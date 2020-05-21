#ifndef _M1PLAYER_LOCKING_QUEUE_H_
#define _M1PLAYER_LOCKING_QUEUE_H_

#include <queue>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <stdexcept>


/**
* Generic thread-safe queue class template using STL mutex and condition_variable.
*
* @tparam T         type that is to be stored in locking queue
* @tparam Container container type that will serve as underlying container
*                   for queue values
*/
template<
	typename T,
	typename Container = std::queue<T>
>
class CLockingQueue {
private:
	/**
	* Lock guard type.
	*/
	typedef std::lock_guard<std::mutex> lock_guard;

public:
	/**
	* Empty queue exception type.
	*/
	class queue_empty {};

	/**
	* Container type.
	*/
	typedef Container container_type;

	/**
	* Value type.
	*/
	typedef typename Container::value_type value_type;

	/**
	* Size type.
	*/
	typedef typename Container::size_type size_type;

	/**
	* Constructs new locking queue.
	*/
	explicit CLockingQueue()
		: unfinished_tasks(0)
	{}

	/**
	* Constructs new locking queue with the copy of the contents of
	* other container.
	*
	* @param[in] other other container to copy the contents from
	*                  when constructing new locking queue.
	*/
	explicit CLockingQueue(const container_type& other)
		: container(other), unfinished_tasks(container.size())
	{}

	/**
	* Checks whether the queue is empty.
	* @return true if the queue is empty, false otherwise
	*/
	bool empty() const {
		lock_guard guard(mutex);
		return container.empty();
	}

	/**
	* Returns the number of elements in the queue.
	* @return the number of elements in the queue.
	*/
	size_type size() const {
		lock_guard guard(mutex);
		return container.size();
	}

	/**
	* Pops an element from the front of the queue and returns it to the
	* caller.
	*
	* If block is true and timeout is a positive integral value then wait for
	* the element to be available in the queue for at most timeout seconds
	* and then throw @a empty exception.
	*
	* This method is the preferred way of popping elements from the queue when
	* the T's assignment operator is guaranteed not to throw any exceptions.
	* In the other case one should use locking_queue::pop_safe().
	*
	* @param[in] block if true, then blocks until an element is available
	* @param[in] timeout number of seconds to wait for the element to be
	*                    available
	* @throws locking_queue::empty in case no elements were available
	* @return the first element of the queue
	*/
	value_type pop(bool block = false, int timeout = 0) {
		std::unique_lock<std::mutex> lock(mutex);

		pop_common(lock, block, timeout);

		value_type element(container.front());
		container.pop();

		return element;
	}

	/**
	* Pops an element from the front of the queue and returns it to the
	* caller in a safe manner.
	*
	* If block is true and timeout is a positive integral value then wait for
	* the element to be available in the queue for at most timeout seconds
	* and then throw @a empty exception.
	*
	* This method is safer than locking_queue#pop() in the way it returns the
	* value to the caller as when an exception is thrown in T's assignment
	* operator the element stays on the queue and is not lost.
	*
	* @param[out] element placeholder for the element that is to be taken from
	*                     the queue
	* @param[in] block if true then blocks until an element is available
	* @param[in] timeout number of seconds to wait for the element to be
	*                    available
	*
	* @sa locking_queue#pop()
	*/
	bool pop_safe(value_type& element, bool block = false, int timeout = 0)
	{
		std::unique_lock<std::mutex> lock(mutex);

		bool ret = pop_common(lock, block, timeout);

		if (ret){
			element = container.front();
			container.pop();
		}

		return ret;
	}

	bool wait_dequeue(value_type& element)
	{
		pop_safe(element, true, -1);
		return true;
	}

	bool timed_wait_dequeue(value_type& element, int timeOut)
	{
		return pop_safe(element, true, timeOut);
	}

	/**
	* Pushes a new element to the back of the queue.
	* @param[in] element element to be pushed to the back of the queue
	*/
	void enqueue(const value_type& element) {
		{
			lock_guard guard(mutex);
			container.push(element);
			unfinished_tasks++;
		}
		non_empty.notify_one();
	}


	/**
	* Reports a previously enqueued task completion.
	*
	* Used by consumer threads to indicate task completion.
	*/
	void task_done() {
		lock_guard guard(mutex);

		unsigned long unfinished = unfinished_tasks - 1;
		if (unfinished < 0) {
			throw std::logic_error("Task done reported more times than the number of elements in the queue");
		}

		if (unfinished == 0) {
			all_tasks_done.notify_all();
		}

		unfinished_tasks = unfinished;
	}

	/**
	* Blocks until all the elements in the queue have been taken from the
	* queue and processed.
	*
	* When an element is pushed onto the queue by means of
	* locking_queue#push(), an internal counter of unfinished tasks is
	* incremented. Then when the element gets popped from the queue and
	* processed one may indicate task completion by means of
	* locking_queue#task_done().
	*
	* When all tasks are done this method unblocks and returns to the caller.
	*/
	void join() const {
		std::unique_lock<std::mutex> lock(mutex);
		while (unfinished_tasks) {
			all_tasks_done.wait(lock);
		}
	}

private:
	bool pop_common(std::unique_lock<std::mutex>& lock, bool block, int timeout)
	{
		if (container.empty())
		{
			if (block){
				if (timeout > 0){
					if (non_empty.wait_for(lock, std::chrono::seconds(timeout)) == std::cv_status::timeout) {
						return false;
					}
					else{
						return true;
					}
				}
				else{
					non_empty.wait(lock);
					return true;
				}
			}
			else{
				return false;
			}
		}
		else{
			return true;
		}
	}

private:
	/**
	* Underlying container that serves as a storage for the queue elements.
	*/
	container_type container;

	/**
	* Container access mutex.
	*/
	mutable std::mutex mutex;

	/**
	* Non empty condition variable.
	*/
	mutable std::condition_variable non_empty;

	/**
	* Unfinished tasks counter.
	*/
	unsigned long unfinished_tasks;

	/**
	* All tasks done condition variable.
	*/
	mutable std::condition_variable all_tasks_done;
};


#endif
