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
	double m_blGjType;		//钢筋类型的及格线比例设定-在构造函数中可以调整
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
	* @brief 数据库获取数据函数 类型计算-通用 用于获取两个工程交集的类型的统计数量  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:标准工程路径
			   const CString& filePathTar：目标/对比工程路径
			   const CString& strComtype：对应的大类的comtype
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [12/28/2020]
	*/
	int GetNum_SameComtype(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes);
			/**
	* @brief 数据库获取数据函数 类型计算-通用 用于获取类型的统计数量    
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:标准工程路径
			   const CString& strComtype：对应的大类的comtype
			   int &nNum：获得的统计值
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [12/28/2020]
	*/
	int GetNum_Comtype(const CString& filePathScr, const CString& strComtypes);
			/**
	* @brief 数据库获取数据函数 钢筋计算 用于获取两个工程交集的钢筋类型的统计数量  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:标准工程路径
			   const CString& filePathTar：目标/对比工程路径
			   const CString& strComtype：对应的大类的comtype
			   int &nNum：获得的统计值
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [12/28/2020]
	*/
	int GetNum_SameGjjbZj(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes);			//钢筋两个工程的交集数据统计
			/**
	* @brief 数据库获取数据函数 钢筋计算 用于获取标准工程的钢筋类型的统计数量  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:标准工程路径
			   const CString& strComtype：对应的大类的comtype
			   int &nNum：获得的统计值
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [12/28/2020]
	*/
	int GetNum_GjjbZj(const CString& filePath, const CString& strComtypes);
	/**
	* @brief 数据库获取数据函数 钢筋计算 用于获取两个工程的钢筋总量的比例  
	*
	*          
	* @note  : 
	* @param : const CString& filePathSrc:标准工程路径
			   const CString& filePathTar：目标/对比工程路径
			   const CString& strComtype：对应的大类的comtypes,例如:202,203
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [12/28/2020]
	*///获取标准工程的钢筋数据
	double GetGjBl(const CString& filePathSrc, const CString& filePathTar, const CString& strComtypes);
	/**
	* @brief 数据库获取数据函数 工程量计算 用于获取两个工程的柱子个数的比例
	*
	*          
	* @note  : 
	* @param : filePathSrc: 标准工程路径
			   filePathTar：目标/对比工程路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [12/29/2020]
	*/
	double GetPoleCountBl(const CString& filePathSrc, const CString& filePathTar);
	/**
	* @brief :从数据库中获取基础部分业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/4/2021]
	*/
	void SetData_JiChu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取柱大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_Zhu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取板大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_Ban(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取梁大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_Liang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的建筑墙大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_Wall_JZ(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的结构墙大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_Wall_JG(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的楼梯大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
			   包括楼梯和梯板
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_MenChuang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的装饰、零星、土方等业务自定义类别所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
			   包括楼梯和梯板
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_Louti(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的装饰、零星、土方等业务自定义类别所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
			   包括楼梯和梯板
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void SetData_Other(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取钢精表单的所需数据，适用所有大类
	*
	*          
	* @note  : 
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/6/2021]
	*/
	void SetData_GJ(const CString& filePathNew, const CString& filePathOld, const GJLX eGjlx);
	/**
	* @brief :从数据库中获取projectinfo表单里面的信息，用于判定是清单模式还是定额模式
	*
	*          
	* @note  : 
	* @param : filePath：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
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
	double GetQDGcl(const CString& filePath, const CString& strComtypes);//数据库获取数据函数
	double GetDEGcl(const CString& filePath, const CString& strComtypes);//数据库获取数据函数
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
	afx_msg void OnBnClickedButtonOpenSrc();												//获取标准工程路径
	afx_msg void OnBnClickedButtonOpenTar();												//获取目标/对比工程路径
	afx_msg void OnBnClickedButtonBase();													//展示基础部分得分 - 测试用
	afx_msg void OnBnClickedButtonPole();													//展示柱部分得分-测试用
	afx_msg void OnBnClickedButtonWallJz();
};