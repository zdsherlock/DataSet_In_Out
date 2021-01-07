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
	/*m_pDataSetTest = NULL;*/
	//��ʼ����������
	//�ֽ������׼����
	m_blGjType = 0.2;
	//����������������
	m_blPoleCount1 = 0.2;
	m_blPoleCount2 = 0.5;
	m_blPoleCount3 = 1;

	//��ʼcomtype,comtype��������ҵ������
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

//��װ��һЩ����

//Ŀ�깤��·����ȡ
void CTest::OnBnClickedButtonOpenTar()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetFilePath(m_fileTarPath);
	m_Edit_Target.SetWindowTextW(m_fileTarPath);
}

//��׼����·����ȡ
void CTest::OnBnClickedButtonOpenSrc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetFilePath(m_fileSrcPath);
	m_Edit_Cur.SetWindowTextW(m_fileSrcPath);
}
//��ȡ�ļ�·������
void CTest::GetFilePath(CString& m_filePath)
{
	BOOL isOpen = TRUE;
	CString filter = _T("(*.pmdb)|*.pmdb|All Files(*.*��|*.*||");

	CFileDialog dlg (isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);

	dlg.GetOFN().lpstrInitialDir = _T("E:\\DSuanLiangTest\\export\\ddll\\���̿�");

	if (dlg.DoModal() == IDOK)
	{
		m_filePath = dlg.GetPathName();
	}
}
////////////////////////////////////////////////�����ݿ��ȡ���ݵĺ���/////////////////////////////////////////////
//��ȡ�嵥ģʽ�����ݿ�����
double CTest::GetQDGcl(const CString& filePath, const CString& strComtypes)
{
	//mainmode = 1 & comtype���� ˫�����޶�
	//�����ݿ�
	CSqliteDataBase db(filePath);
	CSqliteDBStmt stmt(&db);
	//��ʼ������
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

//��ȡ����ģʽ�����ݿ�����
double CTest::GetDEGcl(const CString& filePath, const CString& strComtypes)
{
	//mainmode = 0 & calitemname = 'ʵ��' & unit = 'm3' & comtype����4����
	CSqliteDataBase db(filePath);
	CSqliteDBStmt stmt(&db);
	//��ʼ������
	double dSumQuantity = 0.0;

	CString strSql;
	strSql.Format(_T("SELECT SUM(quantity) AS quantity\
					 FROM\
						(SELECT R.unit,R.calitemname,C.comtype,R.mainmode,R.quantity\
						FROM result AS R\
							LEFT OUTER JOIN components AS C\
								ON R.comid = C.id)\
						WHERE unit = 'm3' AND \
								calitemname = 'ʵ��' AND \
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
	//��ñ�׼���̺�Ŀ�깤�̵Ľ������֣�Ȼ��õ���ͬ�ĸֽ���ֱ����ͳ������
	//��ʼ������
	int nCountAttach = 0;
	//���岢������ʱ���ݿ�
	CSqliteDataBase db(_T(":memory:"));
	CSqliteDBStmt stmt(&db);
	//���������������ݿ⣬������
	stmt.Attach(filePathTar,_T("T"));
	stmt.Attach(filePathSrc,_T("S"));

	//���彻����ȡSQL���
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


	//׼������SQL���
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
	//��ȡsrc�ĸֽ���ֱ����ͳ������
	//��ʼ������
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

	//׼��SQL���ִ��
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
	//��ʼ������
	double dblGjZz = 0.0;
	double dZzTar = 0.0;
	double dZzSrc = 0.0;
	//���������ݿ�
	CSqliteDataBase dbSrc(filePathSrc);
	CSqliteDBStmt stmtSrc(&dbSrc);
	CSqliteDataBase dbTar(filePathTar);
	CSqliteDBStmt stmtTar(&dbTar);

	//׼��SQL���
	CString strSql;
	strSql.Format(_T("SELECT SUM(zz*cc_count) as zz\
					  FROM graphicsresultv2 AS G\
						  LEFT OUTER JOIN components AS C\
							ON G.comid = C.id\
					  WHERE C.comtype IN (%s)"),strComtypes);

	//׼������SQL
	stmtSrc.Prepare(strSql);
	stmtTar.Prepare(strSql);
	int rcSrc = stmtSrc.Step();
	int rcTar = stmtTar.Step();

	//��ȡ����
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

	if (0 != pmcommon::CompareDbl(dZzSrc,0.0) )			//double�����²���ֱ�����Ƚ�
	{
		dblGjZz = dZzTar/dZzSrc;
	}
	else
	{
		MessageBox(_T("��ѡ����ȷ�ı�׼����"));
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
	//��ʼ������
	double dblPoleCount = 0.0;			//��������
	double dPoleCountScore = 0.0;		//����÷�

	//�ֱ������������ݿ�
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
	//��ʼ������
	//�������͵�comtype��
	CString strComtype = m_strComtypeJichu;

	//�������Ͳ��ֵ÷ֱ���
	double dTypeScoreBl = CalcTypeScore(strComtype);

	//���㹤�����÷ֱ���
	double dGclScoreBl = CalcGclScore(strComtype);


	//����ֽ����÷ֱ���
	double dGjScoreBl = CalcGjlScore(strComtype);

	//�����ܷ�
	int iPointType = 10;
	int iPointGcl = 60;
	int iPointGj = 30;
	double dScore = iPointType*dTypeScoreBl + iPointGcl*dGclScoreBl + iPointGj*dGjScoreBl;

	//չʾ����
	CString BaseScore;
	BaseScore.Format(_T("%f, %f, %f, %f"), dTypeScoreBl, dGclScoreBl, dGjScoreBl, dScore);		//�ֱ�Ϊ���ͱ�ֵ����������ֵ���ֽ��ֵ������չʾ��

	return BaseScore; //zdtest ��ʱ����ֵչʾ��
}

CString CTest::CalcPoleScore()
{
	//��ʼ������
	CString strComtype = m_strComtypeZhu;//�������͵�comtype��

	//�������͵÷ֱ���
	double dblTypeScoreBl = CalcTypeScore(strComtype);

	//���㹤�����÷ֱ���
	double dGcl = CalcGclScore(strComtype);
	double dCountPoleBl = GetPoleCountBl(m_fileSrcPath, m_fileTarPath);
	double dGclScoreBl = dGcl * dCountPoleBl;

	//����ֽ����÷ֱ���
	double dGjScoreBl = CalcGjlScore(strComtype);

	//�����ܷ�
	int iPointType = 10;
	int iPointGcl = 60;
	int iPointGj = 30;
	double dScore = iPointType*dblTypeScoreBl + iPointGcl*dGclScoreBl + iPointGj*dGjScoreBl;

	//չʾ����
	CString PoleScore;
	PoleScore.Format(_T("%f, %f, %f, %f"), dblTypeScoreBl, dGclScoreBl, dGjScoreBl, dScore);		//�ֱ�Ϊ���ͱ�ֵ����������ֵ���ֽ��ֵ������չʾ��

	return PoleScore; //zdtest ��ʱ����ֵչʾ��
}


CString CTest::CalcWallScore_JZ()
{


	//���㹤�����÷ֱ���
	//��ͳ��ǽ������
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

	dblScore = dblType; // �ݶ�ֵ������

	return dblScore;
}

double CTest::CalcGjlScore(const CString& strComtypes)
{
	//����ֽ����÷�
	//�ֽ�ֲ�����ʼ��
	int nSumSame = 0;
	int nSumSrc = 0;
	double dblGjType = 0.0;
	double dscore = 0;
	//��ȡ������gjjb,zjͳ������
	nSumSame = GetNum_SameGjjbZj(m_fileSrcPath, m_fileTarPath, strComtypes);
	//��ȡSRC��gjjb,zjͳ������
	nSumSrc = GetNum_GjjbZj(m_fileSrcPath, strComtypes);
	//�����������̸ֽ����͵ı�ֵ
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

	//�������
	double dSumTar = 0.0;
	double dSumSrc = 0.0;
	double dblscore = 0.0;

	//��ȡ����
	if (bMode == 1)
	{
		dSumTar = GetQDGcl(m_fileTarPath, strComtypes);
		dSumSrc = GetQDGcl(m_fileSrcPath, strComtypes);
	}else
	{
		dSumTar = GetDEGcl(m_fileTarPath, strComtypes);
		dSumSrc = GetDEGcl(m_fileSrcPath, strComtypes);
	}

	//���ݴ������ֵ
	if (0 != dSumSrc)
	{
		dblscore = dSumTar/dSumSrc;
	}

	if (dblscore > 1)
	{
		dblscore = 1-(dblscore-1);		//ȡ�����ٷֱ�
	}

	return dblscore;
}

double CTest::CalcGclScore_QH()
{
	//��ȡ��׼���̵�ǽ��
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
		
		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("ǽ��") , strQH ) ;
		int iQH = _ttoi(strQH);
		rc = stmtSrc.Step();
	}
	double a = 1.0;


	//��ȡĿ�깤�̵�ǽ��
	return a;
}

void CTest::SetData_JiChu(const CString& filePathNew, const CString& filePathOld)
{
	CSqliteDataBase dbNew(filePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS jichu");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
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

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
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
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
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

	//���������ݿ��-��������
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS zhu");
	stmtNew.Exec(strSQL_DEL);

	//�����µĹ������͸ֽ��
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

	//�򿪹���project���ݿ�������ݻ�ȡ
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

	//���������ݿ��-��������
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS ban");
	stmtNew.Exec(strSQL_DEL);

	//�����µĹ������͸ֽ��
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

	//�򿪹���project���ݿ�������ݻ�ȡ
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

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS liang");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
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

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
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
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
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

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jz");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
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

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
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
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
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

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jg");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
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

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
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
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
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

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS louti");

	stmtNew.Exec(strSQL_DEL);

	//�����µı�
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

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
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
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
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

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS menchuang");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew = (_T("CREATE TABLE menchuang(id INTEGER,\
													comid INTEGER,\
													comtype INTEGER,\
													cadhandle TEXT,\
													vectorparms BLOB,\
													PRIMARY KEY (id))"));
	int rc = stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
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
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
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

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS other");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
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

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(filePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
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
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
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

	//����comtype���зֱ�
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
	//��ԭ����ȡ���ݴ��뵽�±����
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
	CString strEmode;		//��ʱ��ȷ���÷�����ȡ����0�Ƕ���ģʽ��1���嵥ģʽ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString score = CalcBaseScroe();
	m_Edit_Show_Data.SetWindowTextW(score);
}


void CTest::OnBnClickedButtonPole()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString score = CalcPoleScore();
	m_Edit_Show_Data.SetWindowTextW(score);
}



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
		//����stmtTar�Ѿ���ĳһ��������
		stmtTar.Column_Text(_T("comname"), strTarComname);
		stmtTar.Column_Int(_T("floorid"), nTarFloorid);

		if (!strTarComname.IsEmpty())
		{
			CString strSqlCur;
			strSqlCur.Format(_T("SELECT * FROM components WHERE comname = '%s' AND floorid = %d"), 
				strTarComname, nTarFloorid);
			//����SQL���
			stmtCur.Prepare(strSqlCur);
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
					//��Ĺ���
					CString strColName = _T("vectorparms");
					CProject_VectorParmsTable* pVectorDataSetTar = LoadDataSetVector(stmtTar, strColName);
					UIFunction::TraceDataSet_HTML(pVectorDataSetTar,_T("d:\\zdtest20201223Tar.html"));//zdtest �������
					//��ǰ����
					CProject_VectorParmsTable* pVectorDataSetCur = LoadDataSetVector(stmtCur, strColName);
					UIFunction::TraceDataSet_HTML(pVectorDataSetCur,_T("d:\\zdtest20201223Cur.html"));//zdtest�������

					//�����ű�����ݽ��жԱ�
					int m = pVectorDataSetTar->GetRowCount();//zdtest ���ݼ��
					//���л�ȡ���ݱ�����

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString score = CalcWallScore_JZ();
	m_Edit_Show_Data.SetWindowTextW(score);
}
