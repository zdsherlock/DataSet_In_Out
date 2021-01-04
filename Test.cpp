// Test.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"
//#include "PmReportSource\Common\PmReportCommon.h"
//#include "..\PmBuildReportSouce\Source\Xml\Brick_column_JT.h"
//#include "..\PmBuildReportSouce\Source\ReportMsgAnalyse.h"
//#include "..\PmBuildReportSouce\Source\ReportRelationOpr.h"
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

	//初始化字符串
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

//封装的一些方法
//获取混凝土标号
//CString CTest::GetTqd(const int iComId,const CString & strHandle,const CString& strCalItemName /*= _T("")*/)
//{
//	/// 
//	CString strTqd = _T("");		/// 砼强度
//	int iFloorId = CSLComponentManager::Instance()->GetFloorId( iComId ) ;
//
//	/// 查找楼层
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
//		/// 梁	
//	case Graphic_ComType::LIANG_KL:	/// case 101:
//	case Graphic_ComType::LIANG_CL:	/// case 102:
//	case Graphic_ComType::LIANG_QL:	///case 105:
//	case Graphic_ComType::LIANG_GL:	///case 106:
//	case Graphic_ComType::LIANG_LL:	/// 连梁
//	case Graphic_ComType::LIANG_AL:	/// 过梁
//		/// 柱
//	case Graphic_ComType::ZHU_KZ:	/// case 201:
//	case Graphic_ComType::ZHU_GZ:	///case 202:
//	case Graphic_ComType::ZHU_AZ:	/// case 203:
//	case Graphic_ComType::ZHU_ZM:    /// 柱帽
//		/// 墙
//	case Graphic_ComType::QIANG_TWQ:	/// case 302:
//	case Graphic_ComType::QIANG_TNQ:	/// case 303:
//	case Graphic_ComType::QIANG_DTQ:	/// case 308:
//	case Graphic_ComType::QIANG_JIAYE_QB:
//	case  Graphic_ComType::QIANG_JIAYE_QQ:
//		/// 板
//	case Graphic_ComType::BAN_XB:	/// case 401:
//	case Graphic_ComType::BAN_YB:	///case 402:
//	case Graphic_ComType::BAN_LTB:	///case 403:
//	case Graphic_ComType::BAN_GB:	///case 404:
//	case Graphic_ComType::BAN_QB:	///case 405:
//	case Graphic_ComType::BAN_LXB:	/// 螺旋板
//	case Graphic_ComType::BAN_TB:
//	case Graphic_ComType::BAN_WJX:  /// 屋脊线
//	case Graphic_ComType::BAN_JIAYE: /// 梁板加腋
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
//		/// 门窗
//	case Graphic_ComType::MC_PC:		/// 飘窗
//	case Graphic_ComType::MC_LHC:	 /// 老虎窗
//	case Graphic_ComType::MC_ZPC:	/// 转角飘窗
//	case Graphic_ComType::MC_CTB:	/// 窗台
//	case Graphic_ComType::MC_MD:
//	case Graphic_ComType::MC_MCT:   /// 门窗套
//
//		/// 
//	case Graphic_ComType::ZHU_ZZ:	///case 204:
//	case Graphic_ComType::QIANG_ZWQ:	///case 304:
//	case Graphic_ComType::QIANG_ZNQ:	/// case 305:
//	case Graphic_ComType::QIANG_TCQ:	/// case 306:	
//
//	case Graphic_ComType::QIANG_JBQ: ///间壁墙
//	case Graphic_ComType::QIANG_RFQ:
//
//	case Graphic_ComType::LX_JD: ///  外墙节点
//		{	
//			PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("TQD") , strTqd ) ; 
//			break;
//		}
//	case Graphic_ComType::LIANG_JCL:	///case 104:
//	case Graphic_ComType::LIANG_DKL: /// 地框梁
//	case Graphic_ComType::LIANG_JCLL: /// 基础连梁
//	case Graphic_ComType::LIANG_JCLJY:///基础梁加腋
//		{
//			if (_T("垫层") == strCalItemName ||
//				_T("垫层模板") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("TQD") , strTqd ) ; 
//			}
//			break;
//		}
//		/// 零星
//	case Graphic_ComType::LX_HJD:
//		{	
//			// QC:27413 需求说如果计算项目为"垫层",则垫层砼强度取固定值:C15
//			if (_T("垫层") == strCalItemName)
//			{
//				strTqd = _T("C15");
//			} 
//			else
//			{
//				strTqd = GetHjdTqd(strCalItemName,iFloorId,strHandle);
//			}
//			break;
//		}
//		/// 基础部分
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
//	case Graphic_ComType::JICHU_BZCT: /// 标准承台
//		{
//
//			if (_T("垫层") == strCalItemName ||
//				_T("垫层模板") == strCalItemName)
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
//			if (_T("垫层") == strCalItemName ||
//				_T("垫层模板") == strCalItemName)
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
//			if (_T("底部垫层") == strCalItemName ||
//				_T("侧面垫层") == strCalItemName ||
//				_T("垫层模板") == strCalItemName)
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
//			if (_T("底部垫层") == strCalItemName ||
//				_T("侧面垫层") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("JCTQD") , strTqd ) ; 
//			}
//			break;
//		}
//	case Graphic_ComType::JICHU_JSJ:  /// 集水井
//		{
//
//			if (_T("垫层") == strCalItemName)
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("DCTQD") , strTqd ) ; 
//			} 
//			else
//			{
//				PmPrivateParmOpr.GetComAttribute( iComId , strHandle , _T("JCTQD") , strTqd ) ; 
//			}
//			break;
//		}
//	case Graphic_ComType::JICHU_STJSJ:/// 实体集水井
//		{
//
//			if (_T("底部垫层") == strCalItemName ||
//				_T("侧面垫层") == strCalItemName ||
//				_T("底部垫层模板") == strCalItemName)
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
///////////////////////////////////////////////计分函数/////////////////////////////////////////
CString CTest::CalcBaseScroe()
{
	//初始化参数
	//基础类型的comtype集
	CString strComtype = m_strComtypeBase;

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
	CString strComtype = m_strComtypePole;//基础类型的comtype集

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

//////////////////////////////////////////////////数据计算函数//////////////////////////////////////
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
	int rcSrc = stmtSrc.Step();
	
	int iComid = 0;
	CString strQH;
	
	while (SQLITE_ROW == rcSrc)
	{
		stmtSrc.Column_Int(_T("id"), iComid);
		
		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("墙厚") , strQH ) ;
		int iQH = _ttoi(strQH);
		rcSrc = stmtSrc.Step();
	}
	double a = 1.0;


	//获取目标工程的墙厚
	return a;
}


// CTest 消息处理程序
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
	//	//参数初始化
	//	const void* pBuffer = NULL;
	//	long lBufferSize = 0;

	//	stmtTar.Column_Text(_T("comname"), strComnameTar);
	//	stmtTar.Column_Int(_T("floorid"), iFlooridTar);
	//	stmtTar.Column_Blob(_T("vectorparms"), pBuffer, lBufferSize);


	//	CProject_VectorParmsTable* pVectorDataSetTar = NULL;

	//	pVectorDataSetTar = PMNew(CProject_VectorParmsTable);
	//	pVectorDataSetTar->InitFieldStr();
	//	pVectorDataSetTar->Buffer2DataSet(const_cast<void*>(pBuffer),lBufferSize);

	//	UIFunction::TraceDataSet_HTML(pVectorDataSetTar,_T("d:\\zdtest20201224Cur.html"));//zdtest输出测试

	//	rc = stmtTar.Step();

	//	UIFunction::TraceDataSet_HTML(m_pDataSetTest,_T("d:\\zdtest20201224.html"));//zdtest输出测试
	//	m_pDataSetTest->SetAsString(_T("comname"), iRow, strComnameTar);
	//	UIFunction::TraceDataSet_HTML(m_pDataSetTest,_T("d:\\zdtest20201224.html"));//zdtest输出测试
	//	m_pDataSetTest->SetAsInteger(_T("floorid"), iRow, iFlooridTar);
	//	UIFunction::TraceDataSet_HTML(m_pDataSetTest,_T("d:\\zdtest20201224.html"));//zdtest输出测试
	//	iRow ++;
	//}
	//PMDelete(m_pDataSetTest);
	//m_pDataSetTest = NULL;

}

void CTest::OnBnClickedButtonWallJz()
{
	// TODO: 在此添加控件通知处理程序代码
	CString score = CalcWallScore_JZ();
	m_Edit_Show_Data.SetWindowTextW(score);
}


void CTest::CalcTest()
{

}