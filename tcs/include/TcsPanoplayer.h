#ifndef _TCS_PANOPLAYER_H_
#define _TCS_PANOPLAYER_H_

#include <mutex>
#include <vector>
#include "GLfwSurface.h"
#include "GLPbufferSurface.h"
#include "CapturePixelPanoPlayer.h"

using namespace DetuPanoPlayer;

#define MAX_SURFACE_NUMS 5

typedef struct pano_player_node_t{
	CapturePixelPanoPlayer* pano_player;
	GLOffscreenSurface* surface;
	bool is_used;
}pano_player_node_t;

class CTcsPanoPlayer
{
public:
	static CTcsPanoPlayer& GetInstance()
	{
		if (m_instance == NULL) {
			std::lock_guard<std::mutex> lock(m_mtx);
			if (m_instance == NULL) {
				m_instance = new CTcsPanoPlayer();
			}
			return *m_instance;
		}
		return *m_instance;
	}

public:
	void SetMaxChannels(int nums);
	void CreatSurface();
	GLOffscreenSurface* GetSurface();
	void EnableSurface(GLOffscreenSurface* surface);

private:
	CTcsPanoPlayer();
	~CTcsPanoPlayer();

private:
	static CTcsPanoPlayer* m_instance;
	static std::mutex m_mtx;

	int m_max_live_channels;
	std::mutex m_vector_mtx;
	std::vector<pano_player_node_t*> m_pano_vector;
};

#endif
