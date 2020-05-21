#include "M1PlayerImp.h"
#include "M1Player.h"



CM1Player::CM1Player(bool is_audio_open)
{
	m_player_imp = new CM1PlayerImp(is_audio_open);
}

CM1Player::~CM1Player()
{
	if (m_player_imp){
		m_player_imp->Close();
		delete m_player_imp;
		m_player_imp = NULL;
	}
}

int CM1Player::Init(m1_player_config_s &config)
{
	int ret = 0;
	if (m_player_imp){
		ret = m_player_imp->Init(config);
	}
	return ret;
}

int CM1Player::Play(void)
{
	int ret = 0;
	if (m_player_imp){
		ret = m_player_imp->Play();
	}
	return ret;
}

int CM1Player::RePlay(void)
{
	int ret = 0;
	if (m_player_imp){
		ret = m_player_imp->RePlay();
	}
	return ret;
}

int CM1Player::Close(void)
{
	int ret = 0;
	if (m_player_imp){
		ret = m_player_imp->Close();
		delete m_player_imp;
		m_player_imp = NULL;
	}
	return ret;
}

void CM1Player::SetStreamType(stream_type_e stream_type)
{
	if (m_player_imp){
		m_player_imp->SetStreamType(stream_type);
	}
}

void CM1Player::SetDeocdeType(decode_type_e deocde_type)
{
	if (m_player_imp){
		m_player_imp->SetDeocdeType(deocde_type);
	}
}

void CM1Player::SetDisplayFps(int fps)
{
	if (m_player_imp){
		m_player_imp->SetDisplayFps(fps);
	}
}

void CM1Player::SetRecordTag(bool is_record)
{
	if (m_player_imp){
		m_player_imp->SetRecordTag(is_record);
	}
}

void CM1Player::SetRecordPath(char* path)
{
	if (m_player_imp){
		m_player_imp->SetRecordPath(path);
	}
}

void CM1Player::SetDisplayTag(bool is_display)
{
	if (m_player_imp){
		m_player_imp->SetDisplayTag(is_display);
	}
}

void CM1Player::SetOnwer(long owner_id)
{
	if (m_player_imp){
		m_player_imp->SetOnwer(owner_id);
	}
}

void CM1Player::setDecoderGenerator(IGenerator *decoderGenerator) {
    if(m_player_imp != NULL) {
        m_player_imp->setDecoderGenerator(decoderGenerator);
    }
}


void CM1Player::SetAudioVolume(int volume)
{
	if (m_player_imp != NULL){
		m_player_imp->SetAudioVolume(volume);
	}
}

void CM1Player::PauseAudio(bool pause_on)
{
	if (m_player_imp != NULL){
		m_player_imp->PauseAudio(pause_on);
	}
}
