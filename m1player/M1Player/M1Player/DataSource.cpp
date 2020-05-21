#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include "DataSource.h"
#include "ijksdl_log.h"

#include <assert.h>

CIDataSource::CIDataSource()
{
	m_is_save_flv = false;
	m_sps_pps = NULL;
	m_sps_pps_length = 0;
	m_sps_current_bit = 0;
	m_sync_packet_callback = nullptr;
}

CIDataSource::~CIDataSource()
{
	if (m_sps_pps) {
		free(m_sps_pps);
		m_sps_pps = NULL;
	}
}

int CIDataSource::SockInit(void)
{
#ifdef WIN32
	WORD version;
	WSADATA wsaData;
	version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData) != 0) {
		ALOGE("windows socket init error");
		return -1;
	}
#endif
	return 0;
}

void CIDataSource::SockClean(void)
{
#ifdef WIN32
	WSACleanup();
#endif
}

int CIDataSource::InitSource(std::string url)
{
	return 0;
}

int CIDataSource::HandShake(void)
{
	return 0;
}

int CIDataSource::StartRecv(void)
{
	return 0;
}

int CIDataSource::ReConnet(void)
{
	return 0;
}

int CIDataSource::CloseSource(void)
{
	return 0;
}

void CIDataSource::SetStreamSaveTag(bool save_tag)
{
	return;
}

void CIDataSource::SetStreamSavePath(std::string path)
{
	m_record_path = path;
}

bool CIDataSource::GetStreamSaveTag(void)
{
	return m_is_save_flv;
}

void CIDataSource::SetPacketCallback(stream_packet_callback packet_call_back)
{
	m_sync_packet_callback = packet_call_back;
	return;
}

void CIDataSource::SetMsgCallback(message_callback msg_call_back)
{
	m_message_callback = msg_call_back;
	return;
}

bool CIDataSource::getSpsPpsInfo(SpsPpsInfo* info)
{
	if (info == NULL) {
		return false;
	}
	memset(info, 0, sizeof(SpsPpsInfo));
	info->spsPpsData = (unsigned char*)m_sps_pps;
	info->length = m_sps_pps_length;
	return true;
}

void CIDataSource::parse_sps(unsigned int &width, unsigned int &height)
{
	int frame_crop_left_offset = 0;
	int frame_crop_right_offset = 0;
	int frame_crop_top_offset = 0;
	int frame_crop_bottom_offset = 0;

	int profile_idc = read_bits(8);
	int constraint_set0_flag = read_bit();
	int constraint_set1_flag = read_bit();
	int constraint_set2_flag = read_bit();
	int constraint_set3_flag = read_bit();
	int constraint_set4_flag = read_bit();
	int constraint_set5_flag = read_bit();
	int reserved_zero_2bits = read_bits(2);
	int level_idc = read_bits(8);
	int seq_parameter_set_id = read_exponential_golomb_code();

	if (profile_idc == 100 || profile_idc == 110 ||
		profile_idc == 122 || profile_idc == 244 ||
		profile_idc == 44 || profile_idc == 83 ||
		profile_idc == 86 || profile_idc == 118) {
		int chroma_format_idc = read_exponential_golomb_code();

		if (chroma_format_idc == 3) {
			int residual_colour_transform_flag = read_bit();
		}
		int bit_depth_luma_minus8 = read_exponential_golomb_code();
		int bit_depth_chroma_minus8 = read_exponential_golomb_code();
		int qpprime_y_zero_transform_bypass_flag = read_bit();
		int seq_scaling_matrix_present_flag = read_bit();

		if (seq_scaling_matrix_present_flag) {
			int i = 0;
			for (i = 0; i < 8; i++) {
				int seq_scaling_list_present_flag = read_bit();
				if (seq_scaling_list_present_flag) {
					int sizeOfScalingList = (i < 6) ? 16 : 64;
					int lastScale = 8;
					int nextScale = 8;
					int j = 0;
					for (j = 0; j < sizeOfScalingList; j++) {
						if (nextScale != 0) {
							int delta_scale = read_se();
							nextScale = (lastScale + delta_scale + 256) % 256;
						}
						lastScale = (nextScale == 0) ? lastScale : nextScale;
					}
				}
			}
		}
	}

	int log2_max_frame_num_minus4 = read_exponential_golomb_code();
	int pic_order_cnt_type = read_exponential_golomb_code();
	if (pic_order_cnt_type == 0) {
		int log2_max_pic_order_cnt_lsb_minus4 = read_exponential_golomb_code();
	} else if (pic_order_cnt_type == 1) {
		int delta_pic_order_always_zero_flag = read_bit();
		int offset_for_non_ref_pic = read_bit();
		int offset_for_top_to_bottom_field = read_bit();
		int num_ref_frames_in_pic_order_cnt_cycle = read_exponential_golomb_code();
		int i;
		for (i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++) {
			read_se();
		}
	}
	int max_num_ref_frames = read_exponential_golomb_code();
	int gaps_in_frame_num_value_allowed_flag = read_bit();
	int pic_width_in_mbs_minus1 = read_exponential_golomb_code();
	int pic_height_in_map_units_minus1 = read_exponential_golomb_code();
	int frame_mbs_only_flag = read_bit();
	if (!frame_mbs_only_flag) {
		int mb_adaptive_frame_field_flag = read_bit();
	}
	int direct_8x8_inference_flag = read_bit();
	int frame_cropping_flag = read_bit();
	if (frame_cropping_flag) {
		frame_crop_left_offset = read_exponential_golomb_code();
		frame_crop_right_offset = read_exponential_golomb_code();
		frame_crop_top_offset = read_exponential_golomb_code();
		frame_crop_bottom_offset = read_exponential_golomb_code();
	}
	int vui_parameters_present_flag = read_bit();

	width = ((pic_width_in_mbs_minus1 + 1) * 16) - frame_crop_bottom_offset * 2 - frame_crop_top_offset * 2;
	height = ((2 - frame_mbs_only_flag)* (pic_height_in_map_units_minus1 + 1) * 16) - (frame_crop_right_offset * 2) - (frame_crop_left_offset * 2);
	ALOGE("video width:%d, video height:%d", width, height);
}

unsigned int CIDataSource::read_bit(void)
{
	assert(m_sps_current_bit <= (m_sps_pps_length - 5) * 8);
	int nIndex = m_sps_current_bit / 8;
	int nOffset = m_sps_current_bit % 8 + 1;

	m_sps_current_bit++;
	return (m_sps_pps[nIndex + 5] >> (8 - nOffset)) & 0x01;
}

unsigned int CIDataSource::read_bits(int n)
{
	int r = 0;
	int i;
	for (i = 0; i < n; i++) {
		r |= (read_bit() << (n - i - 1));
	}
	return r;
}

unsigned int CIDataSource::read_se(void)
{
	int r = read_exponential_golomb_code();
	if (r & 0x01) {
		r = (r + 1) / 2;
	} else {
		r = -(r / 2);
	}
	return r;
}

unsigned int CIDataSource::read_exponential_golomb_code(void)
{
	int r = 0;
	int i = 0;

	while ((read_bit() == 0) && (i < 32)) {
		i++;
	}

	r = read_bits(i);
	r += (1 << i) - 1;
	return r;
}
