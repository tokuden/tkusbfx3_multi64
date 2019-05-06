/**************************************************************************//**
 * @file    tkusnfx3.h
 * @brief   ���dUSB FX3���C�u����
 * @details EZ-USB FX3��CyAPI�����b�p����BCC�Ŏg����悤�ɂ��Ă��܂�
 * @todo	
 ******************************************************************************/

#include <Windows.h>

#ifndef TKUSBFX3_API
	#define TKUSBFX3_API __declspec(dllimport)
#endif

// ���̃N���X�� txusbfx3.dll ����G�N�X�|�[�g����܂����B
class Ctxusbfx3 {
public:
	Ctxusbfx3(void);
	// TODO: ���\�b�h�������ɒǉ����Ă��������B
};

#ifdef __cplusplus
	extern "C" {
#endif

typedef enum 
{
	TKUSBFX3_SUCCESS                = 0,
	TKUSBFX3_NOT_OPEN               = -1,
	TKUSBFX3_CY_DEFAULT_FIRMWARE    = -2,
	TKUSBFX3_ENDPOINT_NOTFOUND      = -3,
	TKUSBFX3_LOCK_TIMEOUT           = -4,
	TKUSBFX3_XFER_ERROR             = -5
} TKUSBFX3_ERR;

/*********************************************************************//**
 * @brief		���C�u�������I�[�v������
 * @details		���C�u�������I�[�v������
 * @param		num ���̃p�����[�^���Y�ꂽ�B0���w�肷��΂���
 *              vid ���������f�o�C�X�̃x���_ID���i�[�����
 *              pid ���������f�o�C�X�̃v���_�N�gID���i�[�����
 *              DeviceName ���������f�o�C�X�̖��O���i�[�����
 *              MaxDevnameLength ���O���i�[�����o�b�t�@�̒���
 * @return		����������true��Ԃ��B������Ȃ�������false��Ԃ��B
 **********************************************************************/
TKUSBFX3_API BOOL WINAPI TKUSBFX3Open(int num,unsigned short *vid,unsigned short *pid,char *DeviceName,int MaxDevnameLength);

/*********************************************************************//**
 * @brief		���C�u�������N���[�Y����
 * @details		���C�u�������N���[�Y����
 * @param		�Ȃ�
 * @return		�Ȃ�
 **********************************************************************/
TKUSBFX3_API void  WINAPI TKUSBFX3Close(void);

/*********************************************************************//**
 * @brief		��������FX3�f�o�C�X�̐���Ԃ�
 * @details		��������FX3�f�o�C�X�̐���Ԃ�
 * @param		�Ȃ�
 * @return		���������f�o�C�X�̐�
 **********************************************************************/
TKUSBFX3_API int   WINAPI TKUSBFX3DeviceCount(void);

/*********************************************************************//**
 * @brief		FX3�̓���RAM�ɃC���[�W�t�@�C������������
 * @details		FX3�̓���RAM�ɃC���[�W�t�@�C������������
 * @param		ImageFileName �������ރC���[�W�t�@�C��(*.img)
                ErrorReason �G���[�̌�����������œ���o�b�t�@
                ErrorReasonLength ������o�b�t�@�̒���
 * @return		����������true��Ԃ�
 **********************************************************************/
TKUSBFX3_API BOOL  WINAPI TKUSBFX3WriteToRAM(const char *ImageFileName,char *ErrorReason, int ErrorReasonLength);

/*********************************************************************//**
 * @brief		FX3��SPI ROM�ɃC���[�W�t�@�C������������
 * @details		FX3��SPI ROM�ɃC���[�W�t�@�C������������
 * @param		ImageFileName �������ރC���[�W�t�@�C��(*.img)
                ErrorReason �G���[�̌�����������œ���o�b�t�@
                ErrorReasonLength ������o�b�t�@�̒���
 * @return		����������true��Ԃ�
 **********************************************************************/
TKUSBFX3_API BOOL  WINAPI TKUSBFX3WriteToSPIROM(const char *ImageFileName,char *ErrorReason, int ErrorReasonLength);

/*********************************************************************//**
 * @brief		�჌�x���ȃo���NOUT
 * @details		FX3��API���Ăяo���A�C�ӂ�EndPoint�ɔC�ӂ̒����̃f�[�^��]������
 * @param		ep �G���h�|�C���g�ԍ�
                data ���M�������f�[�^
                length ���M�������f�[�^�̒���(�o�C�g�P��)
 * @return		����������A���M����������Ԃ��B
                USB�f�o�C�X���Ȃ����-1��Ԃ��B
                EZ-USB Loader�̂܂܂ł����-2��Ԃ��B
                �f�[�^�]���Ŏ��s������-3��Ԃ��B
 * @note		1024�o�C�g�P�ʂő��M����ƁA�o�b�t�@�ɗ��܂��Ă��܂����M����Ȃ����Ƃ�����
                128�o�C�g�Ƃ��A�Z���P�ʂő���ƁA�o�b�t�@�ɂ��܂炸�ɂ����ɑ��M�����悤��
 **********************************************************************/
TKUSBFX3_API int   WINAPI TKUSBFX3BulkOut(int ep,unsigned char *data,int length);

/*********************************************************************//**
 * @brief		�჌�x���ȃo���NIn
 * @details		FX3��API���Ăяo���A�C�ӂ�EndPoint����C�ӂ̒����̃f�[�^����M����
 * @param		ep �G���h�|�C���g�ԍ�
                data ��M�����f�[�^���i�[�����o�b�t�@
                length ��M�������f�[�^�̒���(�o�C�g�P��)
 * @return		����������A���M����������Ԃ��B
                USB�f�o�C�X���Ȃ����-1��Ԃ��B
                EZ-USB Loader�̂܂܂ł����-2��Ԃ��B
                �f�[�^�]���Ŏ��s������-3��Ԃ��B
 **********************************************************************/
TKUSBFX3_API int   WINAPI TKUSBFX3BulkIn(int ep,unsigned char *data,int length);

/*********************************************************************//**
 * @brief		�����x���ȑ��M(BulkOut)
 * @details		FPGA�̒���IP�R�A���Ăяo���A�f�[�^�𑗐M����B
 * @param		addr �R�A����o�͂����addr�M���̒l
                data ���M�������f�[�^���i�[�����o�b�t�@
                len ���M�������f�[�^�̒���
                flag �R�A����o�͂����flag�M���̒l
 * @return		����������A���M����������Ԃ��B
                ���s������A0��Ԃ��B
 **********************************************************************/
TKUSBFX3_API int   WINAPI USBWriteData(unsigned long addr,unsigned char *data,int len,unsigned short flag);

/*********************************************************************//**
 * @brief		�����x���Ȏ�M(BulkIn)
 * @details		FPGA�̒���IP�R�A���Ăяo���A�f�[�^����M����B
 * @param		addr �R�A����o�͂����addr�M���̒l
                data ��M�������f�[�^���i�[�����o�b�t�@
                len ��M�������f�[�^�̒���(4�̔{���ɐ؂�グ����)
                flag �R�A����o�͂����flag�M���̒l
 * @return		����������A���M����������Ԃ��B
                ���s������A0��Ԃ��B
 **********************************************************************/
TKUSBFX3_API int   WINAPI USBReadData(unsigned long addr,unsigned char *data,int len,unsigned short flag);

/*********************************************************************//**
 * @brief		�����x���Ȏ�M(BulkIn)
 * @details		FPGA�̒���IP�R�A���Ăяo���A�f�[�^����M����B
 * @param		addr �R�A����o�͂����addr�M���̒l
                data ��M�������f�[�^���i�[�����o�b�t�@
                len ��M�������f�[�^�̒���(4�̔{���ɐ؂�グ����)
                flag �R�A����o�͂����flag�M���̒l
 * @return		����������A���M����������Ԃ��B
                ���s������A0��Ԃ��B
 **********************************************************************/
TKUSBFX3_API int   WINAPI USBReadData(unsigned long addr,unsigned char *data,int len,unsigned short flag);

/*********************************************************************//**
 * @brief		���Z�b�g
 * @details		USB�f�o�C�X�̃��Z�b�g�ƁAUSB�G���h�|�C���g�̃��Z�b�g
 * @param		�Ȃ�
 * @return		�Ȃ�
 **********************************************************************/
TKUSBFX3_API void  WINAPI USBReset(void);

/*********************************************************************//**
 * @brief		�^�C���A�E�g�̐ݒ�
 * @details		USB���牞�����Ȃ��ꍇ�̃^�C���A�E�g���Ԃ�ݒ肷��B�f�t�H���g��10�b�B
 * @param		milliseconds �~���b�P�ʂŃo���N���o�͂̃^�C���A�E�g��ݒ肷��B0xFFFFFFFF��ݒ肷��Ɩ����ɑ҂B
 * @return		�Ȃ�
 **********************************************************************/
TKUSBFX3_API void  WINAPI TKUSBSetTimeout(unsigned long milliseconds);

/*********************************************************************//**
 * @brief		�ő�]���T�C�Y�̐ݒ�
 * @details		1��̓]���ŉ��o�C�g��]�����邩�B�f�t�H���g��1048576�o�C�g�B
 * @param		bytes �]���T�C�Y�B2MB�ȏ�ɂ���Ɠ���̃}�V���Ńn���O�A�b�v����\��������B
 * @return		�Ȃ�
 **********************************************************************/
TKUSBFX3_API void  WINAPI TKUSBSetTransferSize(int bytes);


class CCyUSBDevice;

/*********************************************************************//**
 * @brief		���C�u�������I�[�v������(�����f�o�C�X�Ή���)
 * @details		���C�u�������I�[�v������(�����f�o�C�X�Ή���)
 * @param		num ���̃p�����[�^���Y�ꂽ�B0���w�肷��΂���
 *              vid ���������f�o�C�X�̃x���_ID���i�[�����
 *              pid ���������f�o�C�X�̃v���_�N�gID���i�[�����
 *              DeviceName ���������f�o�C�X�̖��O���i�[�����
 *              MaxDevnameLength ���O���i�[�����o�b�t�@�̒���
 *              Serial ���������f�o�C�X�̃V���A�����i�[�����
 *              MaxSerialLength �V���A�����i�[�����o�b�t�@�̒���
 * @return		���������炻�̃f�o�C�X�̃n���h����Ԃ��B������Ȃ�������NULL��Ԃ��B
 **********************************************************************/
CCyUSBDevice * WINAPI TKUSBFX3OpenEx(int num,unsigned short *vid,unsigned short *pid,char *DeviceName,int MaxDevnameLength,char *Serial,int MaxSerialLength);

/*********************************************************************//**
 * @brief		���C�u�������N���[�Y����
 * @details		���C�u�������N���[�Y����
 * @param		�Ȃ�
 * @return		�Ȃ�
 **********************************************************************/
TKUSBFX3_API void  WINAPI TKUSBFX3CloseEx(CCyUSBDevice *DevHandle);


/*********************************************************************//**
 * @brief		�჌�x���ȃo���NOUT
 * @details		FX3��API���Ăяo���A�C�ӂ�EndPoint�ɔC�ӂ̒����̃f�[�^��]������
 * @param		DevHandle ���삵�����f�o�C�X�̃n���h��
                ep �G���h�|�C���g�ԍ�
                data ���M�������f�[�^
                length ���M�������f�[�^�̒���(�o�C�g�P��)
 * @return		����������A���M����������Ԃ��B
                USB�f�o�C�X���Ȃ����-1��Ԃ��B
                EZ-USB Loader�̂܂܂ł����-2��Ԃ��B
                �f�[�^�]���Ŏ��s������-3��Ԃ��B
 * @note		1024�o�C�g�P�ʂő��M����ƁA�o�b�t�@�ɗ��܂��Ă��܂����M����Ȃ����Ƃ�����
                128�o�C�g�Ƃ��A�Z���P�ʂő���ƁA�o�b�t�@�ɂ��܂炸�ɂ����ɑ��M�����悤��
 **********************************************************************/
TKUSBFX3_API int   WINAPI TKUSBFX3BulkOutEx(CCyUSBDevice *DevHandle,int ep,unsigned char *data,int length);

/*********************************************************************//**
 * @brief		�჌�x���ȃo���NIn
 * @details		FX3��API���Ăяo���A�C�ӂ�EndPoint����C�ӂ̒����̃f�[�^����M����
 * @param		DevHandle ���삵�����f�o�C�X�̃n���h��
                ep �G���h�|�C���g�ԍ�
                data ��M�����f�[�^���i�[�����o�b�t�@
                length ��M�������f�[�^�̒���(�o�C�g�P��)
 * @return		����������A���M����������Ԃ��B
                USB�f�o�C�X���Ȃ����-1��Ԃ��B
                EZ-USB Loader�̂܂܂ł����-2��Ԃ��B
                �f�[�^�]���Ŏ��s������-3��Ԃ��B
 **********************************************************************/
TKUSBFX3_API int   WINAPI TKUSBFX3BulkInEx(CCyUSBDevice *DevHandle,int ep,unsigned char *data,int length);

/*********************************************************************//**
 * @brief		�����x���ȑ��M(BulkOut)
 * @details		FPGA�̒���IP�R�A���Ăяo���A�f�[�^�𑗐M����B
 * @param		DevHandle ���삵�����f�o�C�X�̃n���h��
                addr �R�A����o�͂����addr�M���̒l
                data ���M�������f�[�^���i�[�����o�b�t�@
                len ���M�������f�[�^�̒���
                flag �R�A����o�͂����flag�M���̒l
 * @return		����������A���M����������Ԃ��B
                ���s������A0��Ԃ��B
 **********************************************************************/
TKUSBFX3_API int   WINAPI USBWriteDataEx(CCyUSBDevice *DevHandle,unsigned long addr,unsigned char *data,int len,unsigned short flag);

/*********************************************************************//**
 * @brief		�����x���Ȏ�M(BulkIn)
 * @details		FPGA�̒���IP�R�A���Ăяo���A�f�[�^����M����B
 * @param		DevHandle ���삵�����f�o�C�X�̃n���h��
                addr �R�A����o�͂����addr�M���̒l
                data ��M�������f�[�^���i�[�����o�b�t�@
                len ��M�������f�[�^�̒���(4�̔{���ɐ؂�グ����)
                flag �R�A����o�͂����flag�M���̒l
 * @return		����������A���M����������Ԃ��B
                ���s������A0��Ԃ��B
 **********************************************************************/
TKUSBFX3_API int   WINAPI USBReadDataEx(CCyUSBDevice *DevHandle,unsigned long addr,unsigned char *data,int len,unsigned short flag);


/*********************************************************************//**
 * @brief		FX3�̓���RAM�ɃC���[�W�t�@�C������������
 * @details		FX3�̓���RAM�ɃC���[�W�t�@�C������������
 * @param		num �f�o�C�X�̔ԍ�
                ImageFileName �������ރC���[�W�t�@�C��(*.img)
				ErrorReason �G���[�̌�����������œ���o�b�t�@
				ErrorReasonLength ������o�b�t�@�̒���
 * @return		����������true��Ԃ�
 **********************************************************************/
TKUSBFX3_API BOOL  WINAPI TKUSBFX3WriteToRAMEx(int num, const char* ImageFileName, char* ErrorReason, int ErrorReasonLength);

/*********************************************************************//**
 * @brief		FX3��SPI ROM�ɃC���[�W�t�@�C������������
 * @details		FX3��SPI ROM�ɃC���[�W�t�@�C������������
 * @param		num �f�o�C�X�̔ԍ�
                ImageFileName �������ރC���[�W�t�@�C��(*.img)
				ErrorReason �G���[�̌�����������œ���o�b�t�@
				ErrorReasonLength ������o�b�t�@�̒���
 * @return		����������true��Ԃ�
 **********************************************************************/
TKUSBFX3_API BOOL  WINAPI TKUSBFX3WriteToSPIROMEx(int num, const char* ImageFileName, char* ErrorReason, int ErrorReasonLength);

/*********************************************************************//**
 * @brief		FX3��I2C ROM�ɃC���[�W�t�@�C������������
 * @details		FX3��I2C ROM�ɃC���[�W�t�@�C������������
 * @param		ImageFileName �������ރC���[�W�t�@�C��(*.img)
				ErrorReason �G���[�̌�����������œ���o�b�t�@
				ErrorReasonLength ������o�b�t�@�̒���
 * @return		����������true��Ԃ�
 **********************************************************************/
TKUSBFX3_API BOOL  WINAPI TKUSBFX3WriteToI2CROM(int num, const char* ImageFileName, char* ErrorReason, int ErrorReasonLength);

/*********************************************************************//**
 * @brief		FX3��I2C ROM�ɃC���[�W�t�@�C������������
 * @details		FX3��I2C ROM�ɃC���[�W�t�@�C������������
 * @param		num �f�o�C�X�̔ԍ�
                ImageFileName �������ރC���[�W�t�@�C��(*.img)
				ErrorReason �G���[�̌�����������œ���o�b�t�@
				ErrorReasonLength ������o�b�t�@�̒���
 * @return		����������true��Ԃ�
 **********************************************************************/
TKUSBFX3_API BOOL  WINAPI TKUSBFX3WriteToI2CROMEx(int num, const char* ImageFileName, char* ErrorReason, int ErrorReasonLength);

/*********************************************************************//**
 * @brief		���Z�b�g
 * @details		USB�f�o�C�X�̃��Z�b�g�ƁAUSB�G���h�|�C���g�̃��Z�b�g
 * @param		DevHandle ���삵�����f�o�C�X�̃n���h��
 * @return		�Ȃ�
 **********************************************************************/
TKUSBFX3_API void  WINAPI USBResetEx(CCyUSBDevice* DevHandle);

#ifdef __cplusplus
	}
#endif
