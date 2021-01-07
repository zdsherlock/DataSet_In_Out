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
	/*m_pDataSetTest = NULL;*/
	//初始化比例参数
	//钢筋种类标准参数
	m_blGjType = 0.2;
	//柱子数量比例参数
	m_blPoleCount1 = 0.2;
	m_blPoleCount2 = 0.5;
	m_blPoleCount3 = 1;

	//初始comtype,comtype定义来自业务需求
	m_strComtypeJichu = _T("'503','504','507','501','512','510','511','513','505','506','509','502'");
	m_strComtypeZhu = _T("'201','202','203','204','205'");
	m_strComtypeLiang = _T("'101','102','104,'105','106','107','109','111','112','113','114'");
	m_strComtypeBan = _T("'401','402','404','405'");
	m_strComtypeWall_JZ = _T("'304','305','306','307','309'");
	m_strComtypeWall_JG = _T("'302','303','308','317'");
	m_strComtypeStair = _T("'403','408'");
	m_strComtypeDoor = _T("'601'");
	m_strComtypeWindow = _T("'602'");
	m_strComtypeDecorate = _T("'702','703','704','705','706','707','710','711','712','713'");
	m_strComtypeLouti = _T("'801','802','803','804','805','807','808','811','813','814','815','816','817'");
	m_strComtypeTufang = _T("'1301','1302','1303'");
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
	ON_BN_CLICKED(IDC_BUTTON_OPEN_SOURCE, &CTest::OnBnClickedButtonOpenSrc)
	ON_BN_CLICKED(IDC_BUTTON_Test, &CTest::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_BASE, &CTest::OnBnClickedButtonBase)
	ON_BN_CLICKED(IDC_BUTTON_POLE, &CTest::OnBnClickedButtonPole)
	ON_BN_CLICKED(IDC_BUTTON_WALL_JZ, &CTest::OnBnClickedButtonWallJz)
END_MESSAGE_MAP()

//封装的一些方法

//目标工程路径获取
void CTest::OnBnClickedButtonOpenTar()
{
	// TODO: 在此添加控件通知处理程序代码
	GetFilePath(m_fileTarPath);
	m_Edit_Target.SetWindowTextW(m_fileTarPath);
}

//标准工程路径获取
void CTest::OnBnClickedButtonOpenSrc()
{
	// TODO: 在此添加控件通知处理程序代码
	GetFilePath(m_fileSrcPath);
	m_Edit_Cur.SetWindowTextW(m_fileSrcPath);
}
//获取文件路径方法
void CTest::GetFilePath(CString& m_filePath)
{
	BOOL isOpen = TRUE;
	CString filter = _T("(*.pmdb)|*.pmdb|All Files(*.*）|*.*||");

	CFileDialog dlg (isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);

	dlg.GetOFN().lpstrInitialDir = _T("E:\\DSuanLiangTest\\export\\ddll\\工程库");

	if (dlg.DoModal() == IDOK)
	{
		m_filePath = dlg.GetPathName();
	}
}
////////////////////////////////////////////////从数据库获取数据的函数/////////////////////////////////////////////
//获取清单模式下数据库数据
double CTest::GetQDGcl(const CString& filePath, const CString& strComtypes)
{
	//mainmode = 1 & comtype大类 双条件限定
	//打开数据库
	CSqliteDataBase db(filePath);
	CSqliteDBStmt stmt(&db);
	//初始化参数
	double dSumQuantity = 0.0;

	CString strSql;
	strSql.Format(_T("SELECT SUM(quantity) AS quantity\
					 FROM\
					     (SELECT C.comtype,R.mainmode,R.quantity\
					      FROM result AS R\
					         LEFT OUTER JOIN components AS C\
					             ON R.comid = C.id)\
					      WHERE mainmode = '1' AND\
					      comtype IN (%s)"), strComtypes);

	stmt.Prepare(strSql);
	int rc = stmt.Step();
	double dblQuantity = 0.0;

	if (SQLITE_ROW == rc)
	{
		stmt.Column_Double(_T("quantity"), dblQuantity);
		dSumQuantity =  dblQuantity;
	}

	return dSumQuantity;
}

//获取定额模式下数据库数据
double CTest::GetDEGcl(const CString& filePath, const CString& strComtypes)
{
	//mainmode = 0 & calitemname = '实体' & unit = 'm3' & comtype大类4条件
	CSqliteDataBase db(filePath);
	CSqliteDBStmt stmt(&db);
	//初始化参数
	double dSumQuantity = 0.0;

	CString strSql;
	strSql.Format(_T("SELECT SUM(quantity) AS quantity\
					 FROM\
						(SELECT R.unit,R.calitemname,C.comtype,R.mainmode,R.quantity\
						FROM result AS R\
							LEFT OUTER JOIN components AS C\
								ON R.comid = C.id)\
						WHERE unit = 'm3' AND \
								calitemname = '实体' AND \
								mainmode = '0' AND\
								comtype IN (%s)"), strComtypes);

	stmt.Prepare(strSql);
	int rc = stmt.Step();
	double dblQuantity = 0.0;

	if (SQLITE_ROW == rc)
	{
		stmt.Column_Double(_T("quantity"), dblQuantity);
		dSumQuantity = dblQuantity;
	}

	return dSumQuantity;
}

int CTest::GetNum_SameGjjbZj(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes)
{
	//获得标准工程和目标工程的交集部分，然后得到不同的钢筋级别和直径的统计数据
	//初始化数据
	int nCountAttach = 0;
	//定义并连接临时数据库
	CSqliteDataBase db(_T(":memory:"));
	CSqliteDBStmt stmt(&db);
	//关联两张所需数据库，并命名
	stmt.Attach(filePathTar,_T("T"));
	stmt.Attach(filePathSrc,_T("S"));

	//定义交集获取SQL语句
	CString strSql;
	strSql.Format(_T("SELECT COUNT(*) AS nNum\
					  FROM\
						  (SELECT gjjb,zj\
						   FROM S.graphicsresultv2 AS S_G\
						   LEFT OUTER JOIN S.components AS S_C\
							 ON S_G.comid = S_C.id\
							 WHERE S_C.comtype IN (%s)\
						   INTERSECT\
						   SELECT gjjb,zj\
						   FROM T.graphicsresultv2 AS T_G\
						       LEFT OUTER JOIN T.components AS T_C\
						            ON T_G.comid = T_C.id\
						   WHERE T_C.comtype IN (%s))"),
						   strComtypes, strComtypes); 


	//准备操作SQL语句
	stmt.Prepare(strSql);
	int rc = stmt.Step();

	int nNum = 0;
	if (SQLITE_ROW == rc)
	{
		stmt.Column_Int(_T("nNum"), nNum);
	}

	return nNum;
}

int CTest::GetNum_GjjbZj(const CString& filePath, const CString& strComtypes)
{
	//获取src的钢筋级别和直径的统计数据
	//初始化参数
	int nCountsrc = 0;
	CSqliteDataBase db(filePath);
	CSqliteDBStmt stmt(&db);

	CString strSql;
	strSql.Format(_T("SELECT COUNT(*) AS nNum\
					 FROM\
					 (SELECT gjjb,zj\
					  FROM graphicsresultv2 AS S_G\
					  LEFT OUTER JOIN components AS S_C\
						ON S_G.comid = S_C.id\
					  WHERE S_C.comtype IN (%s)\
					  GROUP BY gjjb,zj)"),
					  strComtypes);

	//准备SQL语句执行
	stmt.Prepare(strSql);
	int rc = stmt.Step();
	
	int nNum = 0;
	if (SQLITE_ROW == rc)
	{
		stmt.Column_Int(_T("nNum"), nNum);
	}
	else
	{
		AfxMessageBox(stmt.ErrMsg());
	}

	return nNum;
}

double CTest::GetGjBl(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes)
{
	//初始化参数
	double dblGjZz = 0.0;
	double dZzTar = 0.0;
	double dZzSrc = 0.0;
	//打开两个数据库
	CSqliteDataBase dbSrc(filePathSrc);
	CSqliteDBStmt stmtSrc(&dbSrc);
	CSqliteDataBase dbTar(filePathTar);
	CSqliteDBStmt stmtTar(&dbTar);

	//准备SQL语句
	CString strSql;
	strSql.Format(_T("SELECT SUM(zz*cc_count) as zz\
					  FROM graphicsresultv2 AS G\
						  LEFT OUTER JOIN components AS C\
							ON G.comid = C.id\
					  WHERE C.comtype IN (%s)"),strComtypes);

	//准备运行SQL
	stmtSrc.Prepare(strSql);
	stmtTar.Prepare(strSql);
	int rcSrc = stmtSrc.Step();
	int rcTar = stmtTar.Step();

	//获取数据
	if (SQLITE_ROW == rcSrc)
	{
		stmtSrc.Column_Double(_T("zz"), dZzSrc);
	}
	else
	{
		AfxMessageBox(stmtSrc.ErrMsg());
	}

	if (SQLITE_ROW == rcTar)
	{
		stmtTar.Column_Double(_T("zz"), dZzTar);
	}
	else
	{
		AfxMessageBox(stmtTar.ErrMsg());
	}

	if (0 != pmcommon::CompareDbl(dZzSrc,0.0) )			//double精度下不能直接做比较
	{
		dblGjZz = dZzTar/dZzSrc;
	}
	else
	{
		MessageBox(_T("请选择正确的标准工程"));
	}

	return dblGjZz;
}

int CTest::GetNum_SameComtype(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes)
{
	CSqliteDataBase db(_T(":memory:"));
	CSqliteDBStmt stmt(&db);

	stmt.Attach(filePathSrc, _T("S"));
	stmt.Attach(filePathTar, _T("T"));

	CString strSql;
	strSql.Format(_T("SELECT COUNT(*) AS nNum\
					  FROM\
						 (SELECT comtype\
						  FROM S.components AS S_C\
						  WHERE comtype in (%s)\
						  INTERSECT\
						  SELECT comtype\
						  FROM T.components AS T_C\
						  WHERE comtype IN (%s))"), strComtypes, strComtypes);

	stmt.Prepare(strSql);
	int rc = stmt.Step();

	int nNum = 0;
	if (SQLITE_ROW == rc)
	{
		stmt.Column_Int(_T("nNum"), nNum);
	}
	else
	{
		AfxMessageBox(stmt.ErrMsg());
	}

	return nNum;
}

int CTest::GetNum_Comtype(const CString& filePathScr, const CString& strComtypes)
{
	CSqliteDataBase db(filePathScr);
	CSqliteDBStmt stmt(&db);

	CString strSql;
	strSql.Format(_T("SELECT Count(*) nNum\
					  FROM\
							(SELECT comtype\
							FROM components\
							WHERE comtype IN (%s)\
							GROUP BY comtype)"), strComtypes);

	stmt.Prepare(strSql);
	int rc = stmt.Step();

	int nNum = 0;
	if (SQLITE_ROW == rc)
	{
		stmt.Column_Int(_T("nNum"), nNum);
	}
	else
	{
		AfxMessageBox(stmt.ErrMsg());
	}

	return nNum;
}

double CTest::GetPoleCountBl(const CString& filePathSrc, const CString& filePathTar)
{
	//初始化参数
	double dblPoleCount = 0.0;			//比例参数
	double dPoleCountScore = 0.0;		//输出得分

	//分别连接两个数据库
	CSqliteDataBase dbSrc(filePathSrc);
	CSqliteDBStmt stmtSrc(&dbSrc);
	CSqliteDataBase dbTar(filePathTar);
	CSqliteDBStmt stmtTar(&dbTar);

	//
	CString strSql;
	strSql.Format(_T("SELECT COUNT(*) AS nNum\
					  FROM\
						  (SELECT R.comid,R.cadhandle\
						   FROM result AS R\
							   LEFT OUTER JOIN components AS C\
									ON R.comid=C.id\
						   WHERE C.comtype in (%s)\
						   GROUP BY R.comid,R.cadhandle)"), m_strComtypeZhu, m_strComtypeZhu);

	stmtSrc.Prepare(strSql);
	stmtTar.Prepare(strSql);

	int rcSrc = stmtSrc.Step();
	int rcTar = stmtTar.Step();

	int nNumSrc = 0;
	if (SQLITE_ROW == rcSrc)
	{
		stmtSrc.Column_Int(_T("nNum"), nNumSrc);
	}

	int nNumTar = 0;
	if (SQLITE_ROW == rcTar)
	{
		stmtTar.Column_Int(_T("nNum"), nNumTar);
	}

	if (0 != nNumSrc)
	{
		dblPoleCount = ((double)(nNumTar))/((double)(nNumSrc));
	}

	if (dblPoleCount < m_blPoleCount1)
	{
		dPoleCountScore = 0.1;
	}
	else if (dblPoleCount < m_blPoleCount2)
	{
		dPoleCountScore = 0.4;
	}
	else if (dblPoleCount < m_blPoleCount3)
	{
		dPoleCountScore = 0.8;
	}
	else if (dblPoleCount == m_blPoleCount3)
	{
		dPoleCountScore = 1;
	}
	else
	{
		dPoleCountScore = 0.8;
	}

	return dPoleCountScore;
};

CString CTest::CalcBaseScroe()
{
	//初始化参数
	//基础类型的comtype集
	CString strComtype = m_strComtypeJichu;

	//计算类型部分得分比例
	double dTypeScoreBl = CalcTypeScore(strComtype);

	//计算工程量得分比例
	double dGclScoreBl = CalcGclScore(strComtype);


	//计算钢筋量得分比例
	double dGjScoreBl = CalcGjlScore(strComtype);

	//计算总分
	int iPointType = 10;
	int iPointGcl = 60;
	int iPointGj = 30;
	double dScore = iPointType*dTypeScoreBl + iPointGcl*dGclScoreBl + iPointGj*dGjScoreBl;

	//展示数据
	CString BaseScore;
	BaseScore.Format(_T("%f, %f, %f, %f"), dTypeScoreBl, dGclScoreBl, dGjScoreBl, dScore);		//分别为类型比值，工程量比值，钢筋比值，测试展示用

	return BaseScore; //zdtest 临时返回值展示用
}

CString CTest::CalcPoleScore()
{
	//初始化参数
	CString strComtype = m_strComtypeZhu;//基础类型的comtype集

	//计算类型得分比例
	double dblTypeScoreBl = CalcTypeScore(strComtype);

	//计算工程量得分比例
	double dGcl = CalcGclScore(strComtype);
	double dCountPoleBl = GetPoleCountBl(m_fileSrcPath, m_fileTarPath);
	double dGclScoreBl = dGcl * dCountPoleBl;

	//计算钢筋量得分比例
	double dGjScoreBl = CalcGjlScore(strComtype);

	//计算总分
	int iPointType = 10;
	int iPointGcl = 60;
	int iPointGj = 30;
	double dScore = iPointType*dblTypeScoreBl + iPointGcl*dGclScoreBl + iPointGj*dGjScoreBl;

	//展示数据
	CString PoleScore;
	PoleScore.Format(_T("%f, %f, %f, %f"), dblTypeScoreBl, dGclScoreBl, dGjScoreBl, dScore);		//分别为类型比值，工程量比值，钢筋比值，测试展示用

	return PoleScore; //zdtest 临时返回值展示用
}


CString CTest::CalcWallScore_JZ()
{


	//计算工程量得分比例
	//先统计墙厚种类
	double dblWallQH = CalcGclScore_QH();

	
	CString b = _T("1.1");

	return b;

};


double CTest::CalcTypeScore(const CString& strComtypes)
{
	int nNumSame = 0;
	int nNumSrc = 0;
	double dblType = 0.0;
	double dblScore = 0.0;

	nNumSame = GetNum_SameComtype(m_fileSrcPath, m_fileTarPath, strComtypes);
	nNumSrc  = GetNum_Comtype(m_fileSrcPath, strComtypes);

	if ( 0 != nNumSrc)
	{
		dblType = ((double)nNumSame) / ((double)nNumSrc);
	}
	else
	{
		dblType = 0.0;
	}

	dblScore = dblType; // 暂定值待调整

	return dblScore;
}

double CTest::CalcGjlScore(const CString& strComtypes)
{
	//计算钢筋量得分
	//钢筋部分参数初始化
	int nSumSame = 0;
	int nSumSrc = 0;
	double dblGjType = 0.0;
	double dscore = 0;
	//获取交集的gjjb,zj统计数据
	nSumSame = GetNum_SameGjjbZj(m_fileSrcPath, m_fileTarPath, strComtypes);
	//获取SRC的gjjb,zj统计数据
	nSumSrc = GetNum_GjjbZj(m_fileSrcPath, strComtypes);
	//计算两个工程钢筋类型的比值
	if ( 0 != nSumSrc)
	{
		dblGjType = ((double)nSumSame) / ((double)nSumSrc);
	}
	else
	{
		dblGjType = 0.0;
	}


	if (dblGjType > m_blGjType)
	{
		dscore = GetGjBl(m_fileSrcPath, m_fileTarPath, strComtypes);
	}
	else
	{
		dscore = 0;
	}

	if (dscore > 1)
	{
		dscore = 1-(dscore-1);
	}

	return dscore;
}

double CTest::CalcGclScore(const CString& strComtypes)
{
	BOOL bMode = FALSE;
	CAccessProject_ProjectInfoTable temProjectInfoTable;
	temProjectInfoTable.GetProjectQDMode(bMode);

	//定义参数
	double dSumTar = 0.0;
	double dSumSrc = 0.0;
	double dblscore = 0.0;

	//获取数据
	if (bMode == 1)
	{
		dSumTar = GetQDGcl(m_fileTarPath, strComtypes);
		dSumSrc = GetQDGcl(m_fileSrcPath, strComtypes);
	}else
	{
		dSumTar = GetDEGcl(m_fileTarPath, strComtypes);
		dSumSrc = GetDEGcl(m_fileSrcPath, strComtypes);
	}

	//数据处理及输出值
	if (0 != dSumSrc)
	{
		dblscore = dSumTar/dSumSrc;
	}

	if (dblscore > 1)
	{
		dblscore = 1-(dblscore-1);		//取正负百分比
	}

	return dblscore;
}

double CTest::CalcGclScore_QH()
{
	//获取标准工程的墙厚
	CSqliteDataBase dbSrc(m_fileSrcPath);
	CSqliteDBStmt stmtSrc(&dbSrc);
	
	CString strSql;
	strSql.Format(_T("SELECT id\
					  FROM components AS C\
		              WHERE C.comtype in (%s)"),m_strComtypeWall_JZ);
	stmtSrc.Prepare(strSql);
	int rc = stmtSrc.Step();
	
	int iComid = 0;
	CString strQH;
	
	while (SQLITE_ROW == rc)
	{
		stmtSrc.Column_Int(_T("id"), iComid);
		
		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("墙厚") , strQH ) ;
		int iQH = _ttoi(strQH);
		rc = stmtSrc.Step();
	}
	double a = 1.0;


	//获取目标工程的墙厚
	return a;
}

void CTest::SetData_JiChu(const CString& filePathNew, const CString& filePathOld)
{
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS jichu");
	stmtNew.Exec(strSQL_DEL);

	//创建新的表单
	CString strSqlNew = (_T("CREATE TABLE jichu(id INTEGER,\
												comid INTEGER,\
												comtype INTEGER,\
												calitemname TEXT,\
												unit TEXT,\
												mainmode INTEGER,\
												vectorparms BLOB,\
												tqd TEXT,\
												gcl REAL,\
												PRIMARY KEY (id))"));
	int rc = stmtNew.Exec(strSqlNew);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//获取result表单数据
	CString strSqlOld;
	strSqlOld.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
						FROM result AS R\
							LEFT OUTER JOIN components AS C\
								ON R.comid = C.id\
						WHERE C.comtype in (%s)"), m_strComtypeJichu);

	stmtOld.Prepare(strSqlOld);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//从工程数据库获取数据并存入新建数据库
	CString strSQLNew_Insert = _T("INSERT INTO jichu(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
											VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSQLNew_Insert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_Zhu(const CString& filePathNew, const CString& filePathOld)
{
	CString strPathNew = filePathNew;
	CSqliteDataBase dbNew(strPathNew);

	//创建新数据库表单-基础部分
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS zhu");
	stmtNew.Exec(strSQL_DEL);

	//创建新的工程量和钢筋表单
	CString strSqlNew = (_T("CREATE TABLE zhu(id INTEGER,\
												   comid INTEGER,\
												   comtype INTEGER,\
												   cadhandle TEXT,\
												   calitemname TEXT,\
												   unit TEXT,\
												   mainmode INTEGER,\
												   vectorparms BLOB,\
												   tqd TEXT,\
												   gcl REAL,\
												   PRIMARY KEY (id))"));
	stmtNew.Exec(strSqlNew);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT *\
						 FROM result AS R\
							  LEFT OUTER JOIN components AS C\
							       on R.comid = C.id\
						 WHERE C.comtype in (%s)"), m_strComtypeZhu);

	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	if (SQLITE_ROW != rc)
	{
		AfxMessageBox(stmtOld.ErrMsg());
	}

	int iComid = 0;
	int iComtype = 0;
	CString strHandle;
	CString strCalitem;
	CString strUnit;
	int iMainmode = 0;
	const void *pBuffer = NULL;
	long lBufferSize = 0;
	CString strTqd;
	double dQuantity = 0.0;

	CString strSQLNew_Insert = _T("INSERT INTO zhu(comid,comtype,cadhandle,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
										VALUES (:comid,:comtype,:cadhandle,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");
	stmtNew.Prepare(strSQLNew_Insert);
	while (SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"), iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitem);
		stmtNew.Bind_Text(_T(":calitemname"), strCalitem);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"), strUnit);

		stmtOld.Column_Int(_T("mainmode"), iMainmode);
		stmtNew.Bind_Int(_T(":mainmode"), iMainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer, lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"), pBuffer, lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_Ban(const CString& filePathNew, const CString& filePathOld)
{
	CString strPathNew = filePathNew;
	CSqliteDataBase dbNew(strPathNew);

	//创建新数据库表单-基础部分
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS ban");
	stmtNew.Exec(strSQL_DEL);

	//创建新的工程量和钢筋表单
	CString strSqlNew = (_T("CREATE TABLE ban(id INTEGER,\
							comid INTEGER,\
							comtype INTEGER,\
							width TEXT,\
							cadhandle TEXT,\
							calitemname TEXT,\
							unit TEXT,\
							mainmode INTEGER,\
							tqd TEXT,\
							gcl REAL,\
							PRIMARY KEY (id))"));
	stmtNew.Exec(strSqlNew);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT *\
						FROM result AS R\
						LEFT OUTER JOIN components AS C\
						on R.comid = C.id\
						WHERE C.comtype in (%s)"), m_strComtypeBan);

	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	if (SQLITE_ROW != rc)
	{
		AfxMessageBox(stmtOld.ErrMsg());
	}

	int iComid = 0;
	int iComtype = 0;
	CString strHandle;
	CString strCalitem;
	CString strUnit;
	int iMainmode = 0;
	const void *pBuffer = NULL;
	long lBufferSize = 0;
	CString strTqd;
	double dQuantity = 0.0;
	CString strWidth;
	CString strSQLNew_Insert = _T("INSERT INTO ban(comid,comtype,width,cadhandle,calitemname,unit,mainmode,tqd,gcl)\
										  VALUES (:comid,:comtype,:width,:cadhandle,:calitemname,:unit,:mainmode,:tqd,:gcl)");
	stmtNew.Prepare(strSQLNew_Insert);
	while (SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"), iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitem);
		stmtNew.Bind_Text(_T(":calitemname"), strCalitem);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"), strUnit);

		stmtOld.Column_Int(_T("mainmode"), iMainmode);
		stmtNew.Bind_Int(_T(":mainmode"), iMainmode);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("Width") , strWidth ) ;
		stmtNew.Bind_Text(_T(":width"), strWidth);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_Liang(const CString& filePathNew, const CString& filePathOld)
{
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS liang");
	stmtNew.Exec(strSQL_DEL);

	//创建新的表单
	CString strSqlNew_GCL = (_T("CREATE TABLE liang(id INTEGER,\
													comid INTEGER,\
													comtype INTEGER,\
													calitemname TEXT,\
													unit TEXT,\
													mainmode INTEGER,\
													vectorparms BLOB,\
													tqd TEXT,\
													gcl REAL,\
													PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//获取result表单数据
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							 FROM result AS R\
								 LEFT OUTER JOIN components AS C\
									ON R.comid = C.id\
							 WHERE C.comtype in (%s)"), m_strComtypeJichu);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//从工程数据库获取数据并存入新建数据库
	CString strSqlInsert = _T("INSERT INTO liang(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
									  VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_Wall_JZ(const CString& filePathNew, const CString& filePathOld)
{

	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jz");
	stmtNew.Exec(strSQL_DEL);

	//创建新的表单
	CString strSqlNew_GCL = (_T("CREATE TABLE wall_jz(id INTEGER,\
													  comid INTEGER,\
													  comtype INTEGER,\
													  width TEXT,\
												      calitemname TEXT,\
													  unit TEXT,\
													  mainmode INTEGER,\
													  tqd TEXT,\
													  gcl REAL,\
													  PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//获取result表单数据
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							 FROM result AS R\
							 LEFT OUTER JOIN components AS C\
							 ON R.comid = C.id\
							 WHERE C.comtype in (%s)"), m_strComtypeWall_JZ);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	CString strWidth;
	double dQuantity = 0.0;
	//从工程数据库获取数据并存入新建数据库
	CString strSqlInsert = _T("INSERT INTO wall_jz(comid,comtype,width,calitemname,unit,mainmode,tqd,gcl)\
									  VALUES (:comid,:comtype,:width,:calitemname,:unit,:mainmode,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("Width") , strWidth ) ;
		stmtNew.Bind_Text(_T(":width"), strWidth);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_Wall_JG(const CString& filePathNew, const CString& filePathOld)
{
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jg");
	stmtNew.Exec(strSQL_DEL);

	//创建新的表单
	CString strSqlNew_GCL = (_T("CREATE TABLE wall_jg(id INTEGER,\
												      comid INTEGER,\
													  comtype INTEGER,\
													  calitemname TEXT,\
													  unit TEXT,\
													  mainmode INTEGER,\
													  vectorparms BLOB,\
													  tqd TEXT,\
													  gcl REAL,\
													  PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//获取result表单数据
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							 FROM result AS R\
							 LEFT OUTER JOIN components AS C\
							 ON R.comid = C.id\
							 WHERE C.comtype in (%s)"), m_strComtypeWall_JG);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//从工程数据库获取数据并存入新建数据库
	CString strSqlInsert = _T("INSERT INTO wall_jg(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
							          VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_Louti(const CString& filePathNew, const CString& filePathOld)
{
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS louti");

	stmtNew.Exec(strSQL_DEL);

	//创建新的表单
	CString strSqlNew_GCL = (_T("CREATE TABLE louti(id INTEGER,\
													comid INTEGER,\
													comtype INTEGER,\
													calitemname TEXT,\
													unit TEXT,\
													mainmode INTEGER,\
													vectorparms BLOB,\
													tqd TEXT,\
													gcl REAL,\
													PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//获取result表单数据
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.transformula\
							 FROM result AS R\
							 LEFT OUTER JOIN components AS C\
							 ON R.comid = C.id\
							 WHERE C.comtype in (%s)"), m_strComtypeStair);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dtransformula = 0.0;
	//从工程数据库获取数据并存入新建数据库
	CString strSqlInsert = _T("INSERT INTO louti(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
									  VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("transformula"), dtransformula);
		stmtNew.Bind_Double(_T(":gcl"), dtransformula);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_MenChuang(const CString& filePathNew, const CString& filePathOld)
{
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS menchuang");
	stmtNew.Exec(strSQL_DEL);

	//创建新的表单
	CString strSqlNew = (_T("CREATE TABLE menchuang(id INTEGER,\
													comid INTEGER,\
													comtype INTEGER,\
													cadhandle TEXT,\
													vectorparms BLOB,\
													PRIMARY KEY (id))"));
	int rc = stmtNew.Exec(strSqlNew);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//获取result表单数据
	CString strSqlOld;
	strSqlOld.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,C.vectorparms\
						 FROM result AS R\
							 LEFT OUTER JOIN components AS C\
								ON R.comid = C.id\
						 WHERE C.comtype in (%s)\
						 OR  C.comtype in (%s)"), m_strComtypeDoor,m_strComtypeWindow);

	stmtOld.Prepare(strSqlOld);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//从工程数据库获取数据并存入新建数据库
	CString strSQLNew_Insert = _T("INSERT INTO menchuang(comid,comtype,cadhandle,vectorparms)\
									      VALUES (:comid,:comtype,:cadhandle,:vectorparms)");

	stmtNew.Prepare(strSQLNew_Insert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}
void CTest::SetData_Other(const CString& filePathNew, const CString& filePathOld)
{
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//清空数据表
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS other");
	stmtNew.Exec(strSQL_DEL);

	//创建新的表单
	CString strSqlNew_GCL = (_T("CREATE TABLE other(id INTEGER,\
														 comid INTEGER,\
														 comtype INTEGER,\
														 calitemname TEXT,\
														 unit TEXT,\
														 mainmode INTEGER,\
														 vectorparms BLOB,\
														 tqd TEXT,\
														 gcl REAL,\
														 PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//打开工程project数据库进行数据获取
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//获取result表单数据
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							 FROM result AS R\
								 LEFT OUTER JOIN components AS C\
									ON R.comid = C.id\
							 WHERE C.comtype IN (%s) OR\
								   C.comtype IN (%s) OR\
								   C.comtype IN (%s)"), m_strComtypeDecorate, m_strComtypeLouti, m_strComtypeTufang);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//从工程数据库获取数据并存入新建数据库
	CString strSqlInsert = _T("INSERT INTO other(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
										 VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CTest::SetData_GJ(const CString& filePathNew, const CString& filePathOld, const GJLX eGjlx)
{
	CString strComtypes;
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);
	stmtNew.Begin();

	//根据comtype进行分表
	CString strTableName;
	switch (eGjlx)
	{
		case eJiChu:
			{
				strTableName = _T("jichu_gj");
				strComtypes = m_strComtypeJichu;
				break;
			}
		case eZhu:
			{
				strTableName = _T("zhu_gj");
				strComtypes = m_strComtypeZhu;
				break;
			}
		case eLiang:
			{
				strTableName = _T("liang_gj");
				strComtypes = m_strComtypeLiang;
				break;
			}
		case eBan:
			{
				strTableName = _T("ban_gj");
				strComtypes = m_strComtypeBan;
				break;
			}
		case eWall_JZ:
			{
				strTableName = _T("wall_jz_gj");
				strComtypes = m_strComtypeWall_JZ;
				break;
			}
		case eLouti:
			{
				strTableName = _T("louti_gj");
				strComtypes = m_strComtypeLouti;
				break;
			}
		default:
			break;
	}

	CString strSQL_Del;
	strSQL_Del.Format(_T("DROP TABLE IF EXISTS %s"), strTableName);
	stmtNew.Exec(strSQL_Del);
	//从原表格获取数据存入到新表格中
	CString strSQLNew;
	strSQLNew.Format(_T("CREATE TABLE %s(id INTEGER,\
										 comid INTEGER,\
										 comtype INTEGER,\
										 gjjb TEXT,\
										 zj REAL,\
										 zz_gj REAL,\
										 PRIMARY KEY (id))"), strTableName);
	stmtNew.Exec(strSQLNew);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT G.comid,C.comtype,G.gjjb,G.zj,G.zz*G.cc_count AS zz_gj\
						 FROM graphicsresultv2 AS G\
							  LEFT OUTER JOIN components AS C\
								   ON G.comid = C.id\
						 WHERE C.comtype in (%s)"), strComtypes);
	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	CString strSQLNew_Insert;
	strSQLNew_Insert.Format(_T("INSERT INTO %s(comid,comtype,gjjb,zj,zz_gj)\
										VALUES (:comid,:comtype,:gjjb,:zj,:zz_gj)"), strTableName);

	stmtNew.Prepare(strSQLNew_Insert);
	int iComid = 0;
	int icomtype = 0;
	CString strGjjb;
	double dzj = 0.0;
	double dzz = 0.0;
	while (SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), icomtype);
		stmtNew.Bind_Int(_T(":comtype"), icomtype);

		stmtOld.Column_Text(_T("gjjb"), strGjjb);
		stmtNew.Bind_Text(_T(":gjjb"), strGjjb);

		stmtOld.Column_Double(_T("zj"), dzj);
		stmtNew.Bind_Double(_T(":zj"), dzj);

		stmtOld.Column_Double(_T("zz_gj"), dzz);
		stmtNew.Bind_Double(_T(":zz_gj"), dzz);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}

	stmtNew.Commit();
}

BOOL CTest::GetQDMode(const CString& filePath)
{
	CSqliteDataBase db(filePath);
	CSqliteDBStmt stmt(&db);

	CString strSQLOld_Emode = _T("SELECT P.parmvalue\
								 FROM projectinfo AS P\
								 WHERE P.parmname = 'QDMode'");
	stmt.Prepare(strSQLOld_Emode);
	int rc = stmt.Step();
	CString strEmode;		//暂时不确定用法，先取出来0是定额模式，1是清单模式
	if (SQLITE_ROW == rc)
	{
		stmt.Column_Text(_T("parmvalue"), strEmode);
	}

	BOOL bEmode = TRUE;

	if (1 == strEmode)
	{
		bEmode = TRUE;
	}
	else
	{
		bEmode = FALSE;
	}
	return bEmode;
}

void CTest::OnBnClickedButtonBase()
{
	// TODO: 在此添加控件通知处理程序代码
	CString score = CalcBaseScroe();
	m_Edit_Show_Data.SetWindowTextW(score);
}


void CTest::OnBnClickedButtonPole()
{
	// TODO: 在此添加控件通知处理程序代码
	CString score = CalcPoleScore();
	m_Edit_Show_Data.SetWindowTextW(score);
}



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

	CSqliteDataBase dbCur(m_fileSrcPath);
	CSqliteDBStmt stmtCur(&dbCur);

	CString strSqlTar = "SELECT * FROM components";
	stmtTar.Prepare(strSqlTar);
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
			CString strSqlCur;
			strSqlCur.Format(_T("SELECT * FROM components WHERE comname = '%s' AND floorid = %d"), 
				strTarComname, nTarFloorid);
			//启动SQL语句
			stmtCur.Prepare(strSqlCur);
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
					//标的工程
					CString strColName = _T("vectorparms");
					CProject_VectorParmsTable* pVectorDataSetTar = LoadDataSetVector(stmtTar, strColName);
					UIFunction::TraceDataSet_HTML(pVectorDataSetTar,_T("d:\\zdtest20201223Tar.html"));//zdtest 输出测试
					//当前工程
					CProject_VectorParmsTable* pVectorDataSetCur = LoadDataSetVector(stmtCur, strColName);
					UIFunction::TraceDataSet_HTML(pVectorDataSetCur,_T("d:\\zdtest20201223Cur.html"));//zdtest输出测试

					//对两张表的数据进行对比
					int m = pVectorDataSetTar->GetRowCount();//zdtest 数据监测
					//逐行获取数据表数据

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
					PMDelete(pVectorDataSetTar);
					pVectorDataSetTar = NULL;
					PMDelete(pVectorDataSetCur);
					pVectorDataSetCur = NULL;
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


CProject_VectorParmsTable* CTest::LoadDataSetVector(CSqliteDBStmt& db, const CString strColName)
{
	CProject_VectorParmsTable* pVectorDataSet = NULL;

	const void* pBuffer = NULL;
	long lBufferSize = 0;

	db.Column_Blob(strColName, pBuffer, lBufferSize);

	pVectorDataSet = PMNew(CProject_VectorParmsTable);
	pVectorDataSet->InitFieldStr();
	pVectorDataSet->Buffer2DataSet(const_cast<void*>(pBuffer),lBufferSize);

	return pVectorDataSet;
}

void CTest::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPathSrc = _T("E:\\ScoreSystem\\srcdatabase.db");
	CString strPathTar = _T("E:\\ScoreSystem\\tardatabase.db");

	//SetData_JiChu(strPathSrc, m_fileSrcPath);
	//SetData_JiChu(strPathTar, m_fileTarPath);
	SetData_Zhu(strPathSrc, m_fileSrcPath);
	SetData_Zhu(strPathTar, m_fileTarPath);
	SetData_Liang(strPathSrc, m_fileSrcPath);
	SetData_Ban(strPathSrc, m_fileSrcPath);
	SetData_Wall_JZ(strPathSrc, m_fileSrcPath);
	SetData_Wall_JG(strPathSrc, m_fileSrcPath);
	SetData_Louti(strPathSrc, m_fileSrcPath);
	SetData_Other(strPathSrc, m_fileSrcPath);
	SetData_MenChuang(strPathSrc, m_fileSrcPath);

	SetData_GJ(strPathSrc, m_fileSrcPath, eJiChu);
	SetData_GJ(strPathTar, m_fileTarPath, eJiChu);
	SetData_GJ(strPathSrc, m_fileSrcPath, eZhu);
	SetData_GJ(strPathTar, m_fileTarPath, eZhu);
}

void CTest::OnBnClickedButtonWallJz()
{
	// TODO: 在此添加控件通知处理程序代码
	CString score = CalcWallScore_JZ();
	m_Edit_Show_Data.SetWindowTextW(score);
}
