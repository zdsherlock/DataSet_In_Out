// Test.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"
//#include "PmReportSource\Common\PmReportCommon.h"
//#include "..\PmBuildReportSouce\Source\Xml\Brick_column_JT.h"
//#include "..\PmBuildReportSouce\Source\ReportMsgAnalyse.h"
//#include "..\PmBuildReportSouce\Source\ReportRelationOpr.h"
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

	//��ʼ���ַ���
	m_strComtypeBase = _T("'503','504','507','104','113','107','114','501','512','510','511','513','505','506','509','502'");
	m_strComtypePole = _T("'201','202','203','204','205'");
	m_strComtypeLiang;
	m_strComtypeBan;
	m_strComtypeWall_JZ = _T("'304','305','306','307','309'");
	m_strComtypeWall_JG;
	m_strComtypeStair;
	m_strComtypeDoor;
	m_strComtypeWindow;
	m_strComtypeDecorate;
	m_strComtypeSatter;
	m_strComtypeTufang;

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
//��ȡ���������
//CString CTest::GetTqd(const int iComId,const CString & strHandle,const CString& strCalItemName /*= _T("")*/)
//{
//	/// 
//	CString strTqd = _T("");		/// ��ǿ��
//	int iFloorId = CSLComponentManager::Instance()->GetFloorId( iComId ) ;
//
//	/// ����¥��
//	if ( ! CPmReportMap::Instance()->FindFloor( iFloorId ) )
//	{
//		return strTqd;
//	}
//
//	CString strComName = CSLComponentManager::Instance()->GetComName( iComId ) ;
//	int iComType = CSLComponentManager::Instance()->GetComType( iComId ) ;
//
//	CString strVectorID = _T("") ; 
//	PmPrivateParmOpr.GetComAttribute( iComId , strHandle , CComParmsSet_ParmName::GJ_ParmType , CComParmsSet_ParmName::VectorID_Gj , strVectorID ) ; 
//	switch(iComType)
//	{
//		/// ��	
//	case Graphic_ComType::LIANG_KL:	/// case 101:
//	case Graphic_ComType::LIANG_CL:	/// case 102:
//	case Graphic_ComType::LIANG_QL:	///case 105:
//	case Graphic_ComType::LIANG_GL:	///case 106:
//	case Graphic_ComType::LIANG_LL:	/// ����
//	case Graphic_ComType::LIANG_AL:	/// ����
//		/// ��
//	case Graphic_ComType::ZHU_KZ:	/// case 201:
//	case Graphic_ComType::ZHU_GZ:	///case 202:
//	case Graphic_ComType::ZHU_AZ:	/// case 203:
//	case Graphic_ComType::ZHU_ZM:    /// ��ñ
//		/// ǽ
//	case Graphic_ComType::QIANG_TWQ:	/// case 302:
//	case Graphic_ComType::QIANG_TNQ:	/// case 303:
//	case Graphic_ComType::QIANG_DTQ:	/// case 308:
//	case Graphic_ComType::QIANG_JIAYE_QB:
//	case  Graphic_ComType::QIANG_JIAYE_QQ:
//		/// ��
//	case Graphic_ComType::BAN_XB:	/// case 401:
//	case Graphic_ComType::BAN_YB:	///case 402:
//	case Graphic_ComType::BAN_LTB:	///case 403:
//	case Graphic_ComType::BAN_GB:	///case 404:
//	case Graphic_ComType::BAN_QB:	///case 405:
//	case Graphic_ComType::BAN_LXB:	/// ������
//	case Graphic_ComType::BAN_TB:
//	case Graphic_ComType::BAN_WJX:  /// �ݼ���
//	case Graphic_ComType::BAN_JIAYE: /// �����Ҹ
//
//
//	case Graphic_ComType::LX_YT:		///case 801:
//	case Graphic_ComType::LX_YP:		///case 802:
//	case Graphic_ComType::LX_SSLX:	///case 804:
//	case Graphic_ComType::LX_YG:		///case 805:
//	case Graphic_ComType::LX_TJ:		/// case 806:
//	case Graphic_ComType::LX_PD:		///case 807:
//	case Graphic_ComType::LX_PSG:	/// case 808:
//	case Graphic_ComType::LX_YaDing:
//	case Graphic_ComType::LX_LanBan:
//	case Graphic_ComType::LX_YTYPZS:
//	case Graphic_ComType::LX_STPD:
//	case Graphic_ComType::LX_STTJ:
//
//		/// �Ŵ�
//	case Graphic_ComType::MC_PC:		/// Ʈ��
//	case Graphic_ComType::MC_LHC:	 /// �ϻ���
//	case Graphic_ComType::MC_ZPC:	/// ת��Ʈ��
//	case Graphic_ComType::MC_CTB:	/// ��̨
//	case Graphic_ComType::MC_MD:
//	case Graphic_ComType::MC_MCT:   /// �Ŵ���
//
//		/// 
//	case Graphic_ComType::ZHU_ZZ:	///case 204:
//	case Graphic_ComType::QIANG_ZWQ:	///case 304:
//	case Graphic_ComType::QIANG_ZNQ:	/// case 305:
//	case Graphic_ComType::QIANG_TCQ:	/// case 306:	
//
//	case Graphic_ComType::QIANG_JBQ: ///���ǽ
//	case Graphic_ComType::QIANG_RFQ:
//
//	case Graphic_ComType::LX_JD: ///  ��ǽ�ڵ�
//		{	
//			PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("TQD") , strTqd ) ; 
//			break;
//		}
//	case Graphic_ComType::LIANG_JCL:	///case 104:
//	case Graphic_ComType::LIANG_DKL: /// �ؿ���
//	case Graphic_ComType::LIANG_JCLL: /// ��������
//	case Graphic_ComType::LIANG_JCLJY:///��������Ҹ
//		{
//			if (_T("���") == strCalItemName ||
//				_T("���ģ��") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("TQD") , strTqd ) ; 
//			}
//			break;
//		}
//		/// ����
//	case Graphic_ComType::LX_HJD:
//		{	
//			// QC:27413 ����˵���������ĿΪ"���",������ǿ��ȡ�̶�ֵ:C15
//			if (_T("���") == strCalItemName)
//			{
//				strTqd = _T("C15");
//			} 
//			else
//			{
//				strTqd = GetHjdTqd(strCalItemName,iFloorId,strHandle);
//			}
//			break;
//		}
//		/// ��������
//	case Graphic_ComType::JICHU_RGZJ:/// case 505:
//	case Graphic_ComType::JICHU_QTZJ:/// case 506:
//	case Graphic_ComType::JICHU_GZZJ:
//		{	
//			PmPrivateParmOpr.GetComAttribute( iComId , strHandle ,  _T("JCTQD") , strTqd ) ; 
//			break;
//		}
//	case Graphic_ComType::JICHU_TTJ:	/// case 501:
//	case Graphic_ComType::JICHU_DLJ:	/// case 503:
//	case Graphic_ComType::JICHU_MTJ:	/// case 507:
//	case Graphic_ComType::JICHU_BZCT: /// ��׼��̨
//		{
//
//			if (_T("���") == strCalItemName ||
//				_T("���ģ��") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("JCTQD") , strTqd ) ; 
//			}
//			break;
//		}
//	case Graphic_ComType::JICHU_ZSJ:	/// case 502:
//		{
//
//			if (_T("���") == strCalItemName ||
//				_T("���ģ��") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("TQD") , strTqd ) ; 
//			}
//			break;
//		}
//	case Graphic_ComType::JICHU_CT:		/// case 504:
//		{
//
//			if (_T("�ײ����") == strCalItemName ||
//				_T("������") == strCalItemName ||
//				_T("���ģ��") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("JCTQD") , strTqd ) ; 
//			}
//			break;
//		}
//	case Graphic_ComType::JICHU_ZD:		/// case 504:
//		{
//
//			if (_T("�ײ����") == strCalItemName ||
//				_T("������") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("JCTQD") , strTqd ) ; 
//			}
//			break;
//		}
//	case Graphic_ComType::JICHU_JSJ:  /// ��ˮ��
//		{
//
//			if (_T("���") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("JCTQD") , strTqd ) ; 
//			}
//			break;
//		}
//	case Graphic_ComType::JICHU_STJSJ:/// ʵ�弯ˮ��
//		{
//
//			if (_T("�ײ����") == strCalItemName ||
//				_T("������") == strCalItemName ||
//				_T("�ײ����ģ��") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("JCTQD") , strTqd ) ; 
//			}
//			break;
//		}
//	default:
//		break;
//	}
//	return strTqd;
//}

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
						   GROUP BY R.comid,R.cadhandle)"), m_strComtypePole, m_strComtypePole);

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
///////////////////////////////////////////////�Ʒֺ���/////////////////////////////////////////
CString CTest::CalcBaseScroe()
{
	//��ʼ������
	//�������͵�comtype��
	CString strComtype = m_strComtypeBase;

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
	CString strComtype = m_strComtypePole;//�������͵�comtype��

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

//////////////////////////////////////////////////���ݼ��㺯��//////////////////////////////////////
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
	int rcSrc = stmtSrc.Step();
	
	int iComid = 0;
	CString strQH;
	
	while (SQLITE_ROW == rcSrc)
	{
		stmtSrc.Column_Int(_T("id"), iComid);
		
		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("ǽ��") , strQH ) ;
		int iQH = _ttoi(strQH);
		rcSrc = stmtSrc.Step();
	}
	double a = 1.0;


	//��ȡĿ�깤�̵�ǽ��
	return a;
}


// CTest ��Ϣ�������
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
	//CString strTqd;
	//CString strhandle = _T("1F20");
	//int icomid = 115;
	//strTqd = GetTqd(icomid, strhandle);
	//int iRow = 0;
	//CProject_SWLExtraValueTable* m_pDataSetTest = PMNew(CProject_SWLExtraValueTable);
	//m_pDataSetTest->InitFieldStr();
	//m_pDataSetTest->InsertRow(0);

	//CSqliteDataBase dbTar(m_fileTarPath);
	//CSqliteDBStmt stmtTar(&dbTar);

	//CSqliteDataBase dbCur(m_fileSrcPath);
	//CSqliteDBStmt stmtCur(&dbCur);

	//CString strSqlComtype = _T("SELECT * FROM components WHERE comtype = 104");

	//stmtTar.Prepare(strSqlComtype);
	//int rc = stmtTar.Step();

	//while (SQLITE_ROW == rc)
	//{
	//	CString strComnameTar;
	//	int iFlooridTar = 0;
	//	//������ʼ��
	//	const void* pBuffer = NULL;
	//	long lBufferSize = 0;

	//	stmtTar.Column_Text(_T("comname"), strComnameTar);
	//	stmtTar.Column_Int(_T("floorid"), iFlooridTar);
	//	stmtTar.Column_Blob(_T("vectorparms"), pBuffer, lBufferSize);


	//	CProject_VectorParmsTable* pVectorDataSetTar = NULL;

	//	pVectorDataSetTar = PMNew(CProject_VectorParmsTable);
	//	pVectorDataSetTar->InitFieldStr();
	//	pVectorDataSetTar->Buffer2DataSet(const_cast<void*>(pBuffer),lBufferSize);

	//	UIFunction::TraceDataSet_HTML(pVectorDataSetTar,_T("d:\\zdtest20201224Cur.html"));//zdtest�������

	//	rc = stmtTar.Step();

	//	UIFunction::TraceDataSet_HTML(m_pDataSetTest,_T("d:\\zdtest20201224.html"));//zdtest�������
	//	m_pDataSetTest->SetAsString(_T("comname"), iRow, strComnameTar);
	//	UIFunction::TraceDataSet_HTML(m_pDataSetTest,_T("d:\\zdtest20201224.html"));//zdtest�������
	//	m_pDataSetTest->SetAsInteger(_T("floorid"), iRow, iFlooridTar);
	//	UIFunction::TraceDataSet_HTML(m_pDataSetTest,_T("d:\\zdtest20201224.html"));//zdtest�������
	//	iRow ++;
	//}
	//PMDelete(m_pDataSetTest);
	//m_pDataSetTest = NULL;

}

void CTest::OnBnClickedButtonWallJz()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString score = CalcWallScore_JZ();
	m_Edit_Show_Data.SetWindowTextW(score);
}


void CTest::CalcTest()
{

}