#ifndef _TEST_MESSAGE_QUEUE_H_
#define _TEST_MESSAGE_QUEUE_H_

#include <memory>
#include <thread>

class TestPlayer;

class TestUI
{
public:
	TestUI();
	~TestUI();

	void Start(void);

public:
	void onMessageHandle1(int message_type, long attach);
	void onMessageHandle2(int message_type, long attach);
	void onMessageHandle3(int message_type, long attach);
	void onMessageHandle4(int message_type, long attach);

private:
	void looper_thread(void);

private:
	long m_signal_id1;
	long m_signal_id2;
	long m_signal_id3;
	long m_signal_id4;

	std::shared_ptr<std::thread>	m_thread;
	TestPlayer*	m_player[4];
	bool m_is_closed;

};

class TestPlayer
{
public:
	TestPlayer();
	~TestPlayer();

	void Start(long owner_id, int duration);

private:
	void looper_thread(void);

private:
	int m_duration;
	long m_owner_id;
	std::shared_ptr<std::thread>	m_thread;
};

#endif
