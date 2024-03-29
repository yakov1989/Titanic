
// StartOpenGLPrjDlg.h : header file
//

#pragma once

#include "glview.h"


// CStartOpenGLPrjDlg dialog
class CStartOpenGLPrjDlg : public CDialogEx
{
// Construction
public:
	CStartOpenGLPrjDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTOPENGLPRJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CGlView* ptrView;
public:
	afx_msg void OnStnClickedCtrlpic();
	afx_msg void OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposRotateX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposRotateY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposRotateZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedResbtn();

	afx_msg void OnTimer(UINT_PTR nIDEvent);


	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
