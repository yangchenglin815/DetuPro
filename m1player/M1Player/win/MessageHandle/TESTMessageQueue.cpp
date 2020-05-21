#include "TESTMessageQueue.h"
#include "MessageQueue.h"

#include <windows.h>

TestUI::TestUI()
{
	m_signal_id1 = 0;
	m_signal_id2 = 0;
	m_signal_id3 = 0;
	m_signal_id4 = 0;

	for (int i = 0; i < 4; i++) {
		m_player[i] = NULL;
	}

	m_is_closed = false;
}

TestUI::~TestUI()
{
	CMessageQueue::GetInstance().Unregister(m_signal_id1);
	CMessageQueue::GetInstance().Unregister(m_signal_id2);
	CMessageQueue::GetInstance().Unregister(m_signal_id3);
	CMessageQueue::GetInstance().Unregister(m_signal_id4);

	m_is_closed = true;
	if (m_thread && m_thread->joinable()) {
		m_thread->join();
	}

	for (int i = 0; i < 4; i++) {
		if (m_player[i]) {
			delete m_player[i];
		}
	}
 
}

void TestUI::Start(void)
{
	for (int i = 0; i < 4; i++) {
		m_player[i] = new TestPlayer;
	}

	CMessageQueue::GetInstance().Register(std::bind(&TestUI::onMessageHandle1, this, std::placeholders::_1, std::placeholders::_2), m_signal_id1);
	CMessageQueue::GetInstance().Register(std::bind(&TestUI::onMessageHandle2, this, std::placeholders::_1, std::placeholders::_2), m_signal_id2);
	CMessageQueue::GetInstance().Register(std::bind(&TestUI::onMessageHandle3, this, std::placeholders::_1, std::placeholders::_2), m_signal_id3);
	CMessageQueue::GetInstance().Register(std::bind(&TestUI::onMessageHandle4, this, std::placeholders::_1, std::placeholders::_2), m_signal_id4);

	m_player[0]->Start(m_signal_id1, 10);
	m_player[1]->Start(m_signal_id2, 10);
	m_player[2]->Start(m_signal_id3, 10);
	m_player[3]->Start(m_signal_id4, 10);

	m_thread.reset(new std::thread(&TestUI::looper_thread, this));
}

void TestUI::onMessageHandle1(int message_type, long attach)
{
	printf("onMessageHandle1, recv message:%d, attach:%ld.\n", message_type, attach);
}

void TestUI::onMessageHandle2(int message_type, long attach)
{
	printf("onMessageHandle2, recv message:%d, attach:%ld.\n", message_type, attach);
}

void TestUI::onMessageHandle3(int message_type, long attach)
{
	printf("onMessageHandle3, recv message:%d, attach:%ld.\n", message_type, attach);
}

void TestUI::onMessageHandle4(int message_type, long attach)
{
	printf("onMessageHandle4, recv message:%d, attach:%ld.\n", message_type, attach);
}

void TestUI::looper_thread(void)
{
	while (true) {
		if (m_is_closed) {
			break;
		}

		Sleep(10);
	}
}

////////////////////////////////////////////////////////////////////////////////////////

TestPlayer::TestPlayer()
{
	m_owner_id = 0;
}

TestPlayer::~TestPlayer()
{
	if (m_thread && m_thread->joinable()) {
		m_thread->join();
	}
}

void TestPlayer::Start(long owner_id, int duration)
{
	m_duration = duration;
	m_owner_id = owner_id;
	m_thread.reset(new std::thread(&TestPlayer::looper_thread, this));
}

void TestPlayer::looper_thread(void)
{
	Sleep(m_duration);
	CMessageQueue::GetInstance().Notify(m_owner_id, m_duration, 0);
}
