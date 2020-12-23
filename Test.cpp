// Test.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"


// CTest 对话框

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


// CTest 消息处理程序


void CTest::OnBnClickedButtonShowData()
{
	// TODO: 在此添加控件通知处理程序代码
	CSqliteDataBase db(m_fileTarPath);

	// 语句对象:在指定的数据库连接上,进行SQL语句操作
	CSqliteDBStmt stmt(&db);

	// 执行SQL语句
	//CString strSQL = _T("SELECT * FROM floor");			//获取楼层
	CString strSQL = _T("SELECT * FROM components");	//获取comid & comname


	stmt.Prepare(strSQL);
	int rc = stmt.Step();

	CString strText;
	// 遍历语句查询出来的记录
	for (int i = 0; SQLITE_ROW == rc; i++)
	{
		// 获取各个列
		stmt.Column_Text(_T("vectorparms"),strText);

		// 遍历下一行记录
		rc = stmt.Step();
		m_Edit_Show_Data.SetWindowTextW(strText);
	}
}


void CTest::OnBnClickedButtonVectorData()
{
	// TODO: 在此添加控件通知处理程序代码
	//打开数据库
	CSqliteDataBase db(m_fileTarPath);

	//指定数据库，并准备语句
	CSqliteDBStmt stmt(&db);

	//定义SQL语句
	CString strSql = _T("SELECT * FROM components WHERE ID = 104");

	//准备执行语句
	stmt.Prepare(strSql);
	int rc = stmt.Step();

	CProject_VectorParmsTable* pVectorDataSet = NULL;
	const void* pBuffer = NULL;
	long lBufferSize = 0;
	while (SQLITE_ROW == rc)
	{
		// 获取各个列
		stmt.Column_Blob(_T("vectorparms"), pBuffer, lBufferSize);
		pVectorDataSet = PMNew(CProject_VectorParmsTable);
		pVectorDataSet->InitFieldStr();
		pVectorDataSet->Buffer2DataSet(const_cast<void*>(pBuffer),lBufferSize);

		UIFunction::TraceDataSet_HTML(pVectorDataSet,_T("d:\\zdtest20201223.html"));

		// 遍历下一行记录
 		rc = stmt.Step();
	}
	PMDelete(pVectorDataSet);
}


void CTest::OnBnClickedButtonBasicCompare()
{
	// TODO: 在此添加控件通知处理程序代码
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
		//这里stmtTar已经是某一行数据了
		stmtTar.Column_Text(_T("comname"), strTarComname);
		stmtTar.Column_Int(_T("floorid"), nTarFloorid);

		if (!strTarComname.IsEmpty())
		{
			CString strSqlGetKeyTwo;
			strSqlGetKeyTwo.Format(_T("SELECT * FROM components WHERE comname = '%s' AND floorid = %d"), 
				strTarComname, nTarFloorid);
			//启动SQL语句
			stmtCur.Prepare(strSqlGetKeyTwo);
			int ircCur = stmtCur.Step();
			//
			while (SQLITE_ROW == ircCur)
			{
				//获取当前工程的comname、floorid；
				stmtCur.Column_Text(_T("comname"),strCurComname);
				stmtCur.Column_Int(_T("floorid"),nCurFloorid);
				//进行判定两张表的comname和floorid是否相同
				if (strTarComname == strCurComname &&
					nTarFloorid == nCurFloorid)
				{
					//在相同的情况下获取vectorparm
					//当前工程
					CProject_VectorParmsTable* pVectorDataSetCur = NULL;
					const void* pBufferCur = NULL;
					long lBufferSizeCur = 0;
					stmtCur.Column_Blob(_T("vectorparms"), pBufferCur, lBufferSizeCur);
					pVectorDataSetCur = PMNew(CProject_VectorParmsTable);
					pVectorDataSetCur->InitFieldStr();
					pVectorDataSetCur->Buffer2DataSet(const_cast<void*>(pBufferCur),lBufferSizeCur);
					//输出测试
					UIFunction::TraceDataSet_HTML(pVectorDataSetCur,_T("d:\\zdtest20201223Cur.html"));

					//标的工程
					CProject_VectorParmsTable* pVectorDataSetTar = NULL;
					const void* pBufferTar = NULL;
					long lBufferSizeTar = 0;
					stmtTar.Column_Blob(_T("vectorparms"), pBufferTar, lBufferSizeTar);
					pVectorDataSetTar = PMNew(CProject_VectorParmsTable);
					pVectorDataSetTar->InitFieldStr();
					pVectorDataSetTar->Buffer2DataSet(const_cast<void*>(pBufferTar),lBufferSizeTar);
					//输出测试
					UIFunction::TraceDataSet_HTML(pVectorDataSetTar,_T("d:\\zdtest20201223Tar.html"));

					//对两张表的数据进行对比
					//test 数据监测
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
	// TODO: 在此添加控件通知处理程序代码
	GetFilePath(m_fileTarPath);
	m_Edit_Target.SetWindowTextW(m_fileTarPath);
}


void CTest::OnBnClickedButtonOpenCur()
{
	// TODO: 在此添加控件通知处理程序代码
	GetFilePath(m_fileCurPath);
	m_Edit_Cur.SetWindowTextW(m_fileCurPath);
}

//获取文件路径方法
void CTest::GetFilePath(CString &m_filePath)
{
	BOOL isOpen = TRUE;
	CString filter = _T("(*.pmdb)|*.pmdb||");

	CFileDialog dlg (isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);

	dlg.GetOFN().lpstrInitialDir = _T("E:\\DSuanLiangTest\\export\\ddll\\工程库");

	if (dlg.DoModal() == IDOK)
	{
		m_filePath = dlg.GetPathName();
	}

}

//获取数据库数据方法，以COMID为依据
void CTest::GetSqlData(CString comnameCur, CString &mfilePath)
{
	//打开数据库
	//CSqliteDataBase db(mfilePath);

	//// 语句对象:在指定的数据库连接上,进行SQL语句操作
	//CSqliteDBStmt stmt(&db);

	////定义SQL语句

	////CString strSql;
	////strSql.Format(_T("SELECT * FROM components where comname=%s"), comnameCur);

	//CString sqlTest = _T("SELECT * FROM components");

	//stmt.Prepare(sqlTest);
	//int rc = stmt.Step();

	//while (SQLITE_ROW == rc)
	//{
	//	// 获取各个列
	//	CString strText;
	//	stmt.Column_Text(_T("comname"), strText);

	//	//UIFunction::TraceDataSet_HTML(strText, _T("d:\\zdtest20201223.html"));

	//	// 遍历下一行记录
	//	rc = stmt.Step();
	//}


}