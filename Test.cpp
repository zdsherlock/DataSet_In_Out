// Test.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"


// CTest �Ի���

IMPLEMENT_DYNAMIC(CTest, CDialog)

CTest::CTest(CWnd* pParent /*=NULL*/)
	: CDialog(CTest::IDD, pParent)
{

}

CTest::~CTest()
{
}

void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TARGET, m_Edit_Target);
	DDX_Control(pDX, IDC_EDIT_SHOW_DATA, m_Edit_Show_Data);
	DDX_Control(pDX, IDC_EDIT_CUR, m_Edit_Cur);
}


BEGIN_MESSAGE_MAP(CTest, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_DATA, &CTest::OnBnClickedButtonShowData)
	ON_BN_CLICKED(IDC_BUTTON_VECTOR_DATA, &CTest::OnBnClickedButtonVectorData)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_COMPARE, &CTest::OnBnClickedButtonBasicCompare)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_TAR, &CTest::OnBnClickedButtonOpenTar)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CUR, &CTest::OnBnClickedButtonOpenCur)
END_MESSAGE_MAP()


// CTest ��Ϣ�������


void CTest::OnBnClickedButtonShowData()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSqliteDataBase db(m_fileTarPath);

	// ������:��ָ�������ݿ�������,����SQL������
	CSqliteDBStmt stmt(&db);

	// ִ��SQL���
	//CString strSQL = _T("SELECT * FROM floor");			//��ȡ¥��
	CString strSQL = _T("SELECT * FROM components");	//��ȡcomid & comname


	stmt.Prepare(strSQL);
	int rc = stmt.Step();

	CString strText;
	// ��������ѯ�����ļ�¼
	for (int i = 0; SQLITE_ROW == rc; i++)
	{
		// ��ȡ������
		stmt.Column_Text(_T("vectorparms"),strText);

		// ������һ�м�¼
		rc = stmt.Step();
		m_Edit_Show_Data.SetWindowTextW(strText);
	}
}


void CTest::OnBnClickedButtonVectorData()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ݿ�
	CSqliteDataBase db(m_fileTarPath);

	//ָ�����ݿ⣬��׼�����
	CSqliteDBStmt stmt(&db);

	//����SQL���
	CString strSql = _T("SELECT * FROM components WHERE ID = 104");

	//׼��ִ�����
	stmt.Prepare(strSql);
	int rc = stmt.Step();

	CProject_VectorParmsTable* pVectorDataSet = NULL;
	const void* pBuffer = NULL;
	long lBufferSize = 0;
	while (SQLITE_ROW == rc)
	{
		// ��ȡ������
		stmt.Column_Blob(_T("vectorparms"), pBuffer, lBufferSize);
		pVectorDataSet = PMNew(CProject_VectorParmsTable);
		pVectorDataSet->InitFieldStr();
		pVectorDataSet->Buffer2DataSet(const_cast<void*>(pBuffer),lBufferSize);

		UIFunction::TraceDataSet_HTML(pVectorDataSet,_T("d:\\zdtest20201223.html"));

		// ������һ�м�¼
 		rc = stmt.Step();
	}
	PMDelete(pVectorDataSet);
}


void CTest::OnBnClickedButtonBasicCompare()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int tarCount = 0;
	int equalCount = 0;

	CSqliteDataBase dbTar(m_fileTarPath);
	CSqliteDBStmt stmtTar(&dbTar);			

	CSqliteDataBase dbCur(m_fileCurPath);
	CSqliteDBStmt stmtCur(&dbCur);

	CString strSqlGetKeySingle = "SELECT * FROM components";
	stmtTar.Prepare(strSqlGetKeySingle);
	int ircTar = stmtTar.Step();

	CString strTarComname;
	int nTarFloorid = 0;

	CString strCurComname;
	int nCurFloorid = 0;
	while (SQLITE_ROW == ircTar)
	{
		//����stmtTar�Ѿ���ĳһ��������
		stmtTar.Column_Text(_T("comname"), strTarComname);
		stmtTar.Column_Int(_T("floorid"), nTarFloorid);

		if (!strTarComname.IsEmpty())
		{
			CString strSqlGetKeyTwo;
			strSqlGetKeyTwo.Format(_T("SELECT * FROM components WHERE comname = '%s' AND floorid = %d"), 
				strTarComname, nTarFloorid);
			//����SQL���
			stmtCur.Prepare(strSqlGetKeyTwo);
			int ircCur = stmtCur.Step();
			//
			while (SQLITE_ROW == ircCur)
			{
				//��ȡ��ǰ���̵�comname��floorid��
				stmtCur.Column_Text(_T("comname"),strCurComname);
				stmtCur.Column_Int(_T("floorid"),nCurFloorid);
				//�����ж����ű��comname��floorid�Ƿ���ͬ
				if (strTarComname == strCurComname &&
					nTarFloorid == nCurFloorid)
				{
					//����ͬ������»�ȡvectorparm
					//��ǰ����
					CProject_VectorParmsTable* pVectorDataSetCur = NULL;
					const void* pBufferCur = NULL;
					long lBufferSizeCur = 0;
					stmtCur.Column_Blob(_T("vectorparms"), pBufferCur, lBufferSizeCur);
					pVectorDataSetCur = PMNew(CProject_VectorParmsTable);
					pVectorDataSetCur->InitFieldStr();
					pVectorDataSetCur->Buffer2DataSet(const_cast<void*>(pBufferCur),lBufferSizeCur);
					//�������
					UIFunction::TraceDataSet_HTML(pVectorDataSetCur,_T("d:\\zdtest20201223Cur.html"));

					//��Ĺ���
					CProject_VectorParmsTable* pVectorDataSetTar = NULL;
					const void* pBufferTar = NULL;
					long lBufferSizeTar = 0;
					stmtTar.Column_Blob(_T("vectorparms"), pBufferTar, lBufferSizeTar);
					pVectorDataSetTar = PMNew(CProject_VectorParmsTable);
					pVectorDataSetTar->InitFieldStr();
					pVectorDataSetTar->Buffer2DataSet(const_cast<void*>(pBufferTar),lBufferSizeTar);
					//�������
					UIFunction::TraceDataSet_HTML(pVectorDataSetTar,_T("d:\\zdtest20201223Tar.html"));

					//�����ű�����ݽ��жԱ�
					//test ���ݼ��
					int m = pVectorDataSetTar->GetRowCount();

					for (int h = 1; h <= m; h++)
					{
						CString strNameTar = pVectorDataSetTar->GetAsString(CProject_VectorParmsTable::CFieldInfo::parmname, h);
						CString strValueTar = pVectorDataSetTar->GetAsString(CProject_VectorParmsTable::CFieldInfo::parmvalue, h);

						CString strNameCur = pVectorDataSetCur->GetAsString(CProject_VectorParmsTable::CFieldInfo::parmname, h);
						CString strValueCur = pVectorDataSetCur->GetAsString(CProject_VectorParmsTable::CFieldInfo::parmvalue, h);

						if (strNameTar == strNameCur && strValueTar == strValueCur)
						{
							equalCount++;
						}
						else
						{
							break;
						}

					}

					/// test 
					//for( int h = 1; h <= pVectorDataSetTar->GetRowCount(); h++)
					//{
					//	CString strName = pVectorDataSetTar->GetAsString(CProject_VectorParmsTable::CFieldInfo::parmname,h);
					//	CString strValue = pVectorDataSetTar->GetAsString(CProject_VectorParmsTable::CFieldInfo::parmvalue,h);
					//}

				}
				ircCur = stmtCur.Step();
			}
		}
		ircTar = stmtTar.Step();
		tarCount++;
	}

	double GjPercent = equalCount/tarCount;
	CString strGjPercent;
	strGjPercent.Format(_T("%f"), GjPercent);

	m_Edit_Show_Data.SetWindowTextW(strGjPercent);

}




void CTest::OnBnClickedButtonOpenTar()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetFilePath(m_fileTarPath);
	m_Edit_Target.SetWindowTextW(m_fileTarPath);
}


void CTest::OnBnClickedButtonOpenCur()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetFilePath(m_fileCurPath);
	m_Edit_Cur.SetWindowTextW(m_fileCurPath);
}

//��ȡ�ļ�·������
void CTest::GetFilePath(CString &m_filePath)
{
	BOOL isOpen = TRUE;
	CString filter = _T("(*.pmdb)|*.pmdb||");

	CFileDialog dlg (isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);

	dlg.GetOFN().lpstrInitialDir = _T("E:\\DSuanLiangTest\\export\\ddll\\���̿�");

	if (dlg.DoModal() == IDOK)
	{
		m_filePath = dlg.GetPathName();
	}

}

//��ȡ���ݿ����ݷ�������COMIDΪ����
void CTest::GetSqlData(CString comnameCur, CString &mfilePath)
{
	//�����ݿ�
	//CSqliteDataBase db(mfilePath);

	//// ������:��ָ�������ݿ�������,����SQL������
	//CSqliteDBStmt stmt(&db);

	////����SQL���

	////CString strSql;
	////strSql.Format(_T("SELECT * FROM components where comname=%s"), comnameCur);

	//CString sqlTest = _T("SELECT * FROM components");

	//stmt.Prepare(sqlTest);
	//int rc = stmt.Step();

	//while (SQLITE_ROW == rc)
	//{
	//	// ��ȡ������
	//	CString strText;
	//	stmt.Column_Text(_T("comname"), strText);

	//	//UIFunction::TraceDataSet_HTML(strText, _T("d:\\zdtest20201223.html"));

	//	// ������һ�м�¼
	//	rc = stmt.Step();
	//}


}