#pragma once
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// CTest 对话框

class CTest : public CDialog
{
	DECLARE_DYNAMIC(CTest)

public:
	CTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTest();

// 对话框数据
	enum { IDD = IDD_DIALOG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	/*void TestSql(CString filePath);*/
	/*virtual BOOL OnInitDialog();*/
	void GetFilePath(CString &m_filePath);	
	void GetSqlData(CString comnameCur, CString &mfilePath);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenTar();
	afx_msg void OnBnClickedButtonOpenCur();
	afx_msg void OnBnClickedButtonShowData();
	afx_msg void OnBnClickedButtonVectorData();
	afx_msg void OnBnClickedButtonBasicCompare();

private:
	CString m_fileTarPath;
	CString m_fileCurPath;

public:
	/*CListCtrl m_List_Show_Data;*/
	CEdit m_Edit_Target;

	CEdit m_Edit_Show_Data;

	CEdit m_Edit_Cur;

};
