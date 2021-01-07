#pragma once
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// CTest �Ի���

class CTest : public CDialog
{
	DECLARE_DYNAMIC(CTest)

public:
	CTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTest();

// �Ի�������
	enum { IDD = IDD_DIALOG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	enum GJLX
	{
		eJiChu,
		eZhu,
		eLiang,
		eBan,
		eLouti,
		eWall_JZ,
	};
	double m_blGjType;		//�ֽ����͵ļ����߱����趨-�ڹ��캯���п��Ե���
	double m_blPoleCount1;
	double m_blPoleCount2;
	double m_blPoleCount3;

	CString m_strComtypeJichu;
	CString m_strComtypeZhu;
	CString m_strComtypeLiang;
	CString m_strComtypeBan;
	CString m_strComtypeWall_JZ;
	CString m_strComtypeWall_JG;
	CString m_strComtypeStair;
	CString m_strComtypeDoor;
	CString m_strComtypeWindow;
	CString m_strComtypeDecorate;
	CString m_strComtypeLouti;
	CString m_strComtypeTufang;

	CString m_fileTarPath;
	CString m_fileSrcPath;
	CEdit m_Edit_Target;
	CEdit m_Edit_Show_Data;
	CEdit m_Edit_Cur;


public:
	/**
	* @brief ���ݿ��ȡ���ݺ��� ���ͼ���-ͨ�� ���ڻ�ȡ�������̽��������͵�ͳ������  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:��׼����·��
			   const CString& filePathTar��Ŀ��/�Աȹ���·��
			   const CString& strComtype����Ӧ�Ĵ����comtype
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [12/28/2020]
	*/
	int GetNum_SameComtype(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes);
			/**
	* @brief ���ݿ��ȡ���ݺ��� ���ͼ���-ͨ�� ���ڻ�ȡ���͵�ͳ������    
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:��׼����·��
			   const CString& strComtype����Ӧ�Ĵ����comtype
			   int &nNum����õ�ͳ��ֵ
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [12/28/2020]
	*/
	int GetNum_Comtype(const CString& filePathScr, const CString& strComtypes);
			/**
	* @brief ���ݿ��ȡ���ݺ��� �ֽ���� ���ڻ�ȡ�������̽����ĸֽ����͵�ͳ������  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:��׼����·��
			   const CString& filePathTar��Ŀ��/�Աȹ���·��
			   const CString& strComtype����Ӧ�Ĵ����comtype
			   int &nNum����õ�ͳ��ֵ
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [12/28/2020]
	*/
	int GetNum_SameGjjbZj(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes);			//�ֽ��������̵Ľ�������ͳ��
			/**
	* @brief ���ݿ��ȡ���ݺ��� �ֽ���� ���ڻ�ȡ��׼���̵ĸֽ����͵�ͳ������  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:��׼����·��
			   const CString& strComtype����Ӧ�Ĵ����comtype
			   int &nNum����õ�ͳ��ֵ
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [12/28/2020]
	*/
	int GetNum_GjjbZj(const CString& filePath, const CString& strComtypes);
	/**
	* @brief ���ݿ��ȡ���ݺ��� �ֽ���� ���ڻ�ȡ�������̵ĸֽ������ı���  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:��׼����·��
			   const CString& filePathTar��Ŀ��/�Աȹ���·��
			   const CString& strComtype����Ӧ�Ĵ����comtypes,����:202,203
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [12/28/2020]
	*///��ȡ��׼���̵ĸֽ�����
	double GetGjBl(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes);
	/**
	* @brief ���ݿ��ȡ���ݺ��� ���������� ���ڻ�ȡ�������̵����Ӹ����ı���
	*
	*          
	* @note  : 
	* @param : filePathSrc: ��׼����·��
			   filePathTar��Ŀ��/�Աȹ���·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [12/29/2020]
	*/
	double GetPoleCountBl(const CString& filePathSrc, const CString& filePathTar);
	/**
	* @brief :�����ݿ��л�ȡ��������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/4/2021]
	*/
	void SetData_JiChu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_Zhu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_Ban(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_Liang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ���Ľ���ǽ����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_Wall_JZ(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ���Ľṹǽ����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_Wall_JG(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ����¥�ݴ���ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
			   ����¥�ݺ��ݰ�
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_MenChuang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ����װ�Ρ����ǡ�������ҵ���Զ��������������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
			   ����¥�ݺ��ݰ�
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_Louti(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ����װ�Ρ����ǡ�������ҵ���Զ��������������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
			   ����¥�ݺ��ݰ�
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void SetData_Other(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�־������������ݣ��������д���
	*
	*          
	* @note  : 
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/6/2021]
	*/
	void SetData_GJ(const CString& filePathNew, const CString& filePathOld, const GJLX eGjlx);
	/**
	* @brief :�����ݿ��л�ȡprojectinfo���������Ϣ�������ж����嵥ģʽ���Ƕ���ģʽ
	*
	*          
	* @note  : 
	* @param : filePath�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	BOOL GetQDMode(const CString& filePath);
	CString CalcBaseScroe();
	CString CalcPoleScore();
	void CalcLiangScore();
	void CalcBanScore();
	CString CalcWallScore_JZ();
	void CalcWallScore_JG();
	void CalcStairScore();
	void CalcDoorScore();
	void CalcWindowScore();
	void CalcDecorateScore();
	void CalcSatterScore();
	void CalcTufangScore();
	double GetQDGcl(const CString& filePath, const CString& strComtypes);//���ݿ��ȡ���ݺ���
	double GetDEGcl(const CString& filePath, const CString& strComtypes);//���ݿ��ȡ���ݺ���
	double CalcTypeScore(const CString& strComtypes);
	double CalcGclScore(const CString& strComtypes);
	double CalcGjlScore(const CString& strComtypes);
	double CalcGclScore_QH();
	void GetFilePath(CString& m_filePath);
	CProject_VectorParmsTable* LoadDataSetVector(CSqliteDBStmt& db, const CString strColName);
	afx_msg void OnBnClickedButtonShowData();
	afx_msg void OnBnClickedButtonVectorData();
	afx_msg void OnBnClickedButtonBasicCompare();
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnBnClickedButtonOpenSrc();												//��ȡ��׼����·��
	afx_msg void OnBnClickedButtonOpenTar();												//��ȡĿ��/�Աȹ���·��
	afx_msg void OnBnClickedButtonBase();													//չʾ�������ֵ÷� - ������
	afx_msg void OnBnClickedButtonPole();													//չʾ�����ֵ÷�-������
	afx_msg void OnBnClickedButtonWallJz();
};