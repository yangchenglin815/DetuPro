#pragma once

#include <deque>
#include <opencv2/core/core.hpp>

#include "boost/thread.hpp"

namespace moodycamel{
	template<typename ItemType>
	class BlockingReaderWriterQueue
	{
		enum { DEFAULT_QUEUE_SIZE = 9000, MAX_QUEUE_SIZE = 9000 };
	public:
		BlockingReaderWriterQueue(int maxSize_ = DEFAULT_QUEUE_SIZE) :
			maxSize(maxSize_ <= 0 ? DEFAULT_QUEUE_SIZE : (maxSize_ > MAX_QUEUE_SIZE ? MAX_QUEUE_SIZE : maxSize_)), pass(0) {};

		bool enqueueBySize(const ItemType& item)
		{
			bool ret = true;
			boost::lock_guard<boost::mutex> lock(mtxQueue);
			if (queue.size() > maxSize){
				queue.pop_back();
			}
			queue.push_front(item);
			condNonEmpty.notify_one();


			return ret;
		}
		bool enqueue(const ItemType& item)
		{
			bool ret = true;
			boost::lock_guard<boost::mutex> lock(mtxQueue);
			queue.push_front(item);
			condNonEmpty.notify_one();


			return ret;
		}
		bool enqueueBack(const ItemType& item)
		{
			bool ret = true;
			boost::lock_guard<boost::mutex> lock(mtxQueue);
			queue.push_back(item);
			condNonEmpty.notify_one();
			return ret;
		}

		bool dequeue(ItemType& item)
		{
			boost::lock_guard<boost::mutex> lock(mtxQueue);

			if (queue.empty())
			{
				return false;
			}
			item = queue.back();
			queue.pop_back();

			return true;
		}
		bool wait_dequeue(ItemType& item)
		{
			boost::unique_lock<boost::mutex> lock(mtxQueue);
		
			while (queue.empty() && !pass)
			{
				condNonEmpty.wait(lock);
			}
			if (pass)
			{
				item = ItemType();
				return false;
			}

			item = queue.back();
			queue.pop_back();

			return true;
		}
		void clear()
		{
			boost::lock_guard<boost::mutex> lock(mtxQueue);
			queue.clear();
		}
		int size()
		{
			boost::lock_guard<boost::mutex> lock(mtxQueue);
			return queue.size();
		}
		void stop()
		{
			pass = 1;
			condNonEmpty.notify_one();
		}
		void resume()
		{
			pass = 0;
		}

	private:
		int maxSize;
		std::deque<ItemType> queue;
		boost::mutex mtxQueue;
		boost::condition_variable condNonEmpty;
		int pass;
	};
}
