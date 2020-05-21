#include "TcsPanoplayer.h"

CTcsPanoPlayer* CTcsPanoPlayer::m_instance = NULL;
std::mutex CTcsPanoPlayer::m_mtx;

CTcsPanoPlayer::CTcsPanoPlayer()
{
	m_max_live_channels = MAX_SURFACE_NUMS;
}

CTcsPanoPlayer::~CTcsPanoPlayer()
{
	std::vector<pano_player_node_t*>::iterator iter = m_pano_vector.begin();
	for (; iter != m_pano_vector.end();){
		pano_player_node_t* node = *iter;
		delete node->pano_player;
		delete node->surface;
		iter = m_pano_vector.erase(iter);
		free(node);
	}
}

void CTcsPanoPlayer::SetMaxChannels(int nums)
{
	m_max_live_channels = nums;
}

void CTcsPanoPlayer::CreatSurface()
{
	std::lock_guard<std::mutex> lock(m_vector_mtx);
	for (int i = 0; i < m_max_live_channels;i++){
		pano_player_node_t* node = (pano_player_node_t*)malloc(sizeof(pano_player_node_t));
		node->pano_player = new CapturePixelPanoPlayer;
		node->surface = new GlfwSurface(node->pano_player);
		node->is_used = false;
		m_pano_vector.push_back(node);
	}
}

GLOffscreenSurface* CTcsPanoPlayer::GetSurface()
{
	std::lock_guard<std::mutex> lock(m_vector_mtx);
	for (int i = 0; i < m_pano_vector.size();i++){
		pano_player_node_t* node = m_pano_vector.at(i);
		if (!node->is_used){
			node->is_used = true;
			return node->surface;
		}
	}
	return NULL;
}

void CTcsPanoPlayer::EnableSurface(GLOffscreenSurface* surface)
{
	std::lock_guard<std::mutex> lock(m_vector_mtx);
	for (int i = 0; i < m_pano_vector.size(); i++){
		pano_player_node_t* node = m_pano_vector.at(i);
		if (node->surface == surface){
			node->is_used = false;
		}
	}
}
