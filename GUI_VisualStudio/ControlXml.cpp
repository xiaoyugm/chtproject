// Filename: ControlXml.cpp
// 29-Nov-2006 nschan Initial revision. 
//
// Note: The ReadFile() method is derived from Ben Bryant's MarkupDlg.cpp class
//       from the markup demo.

#include "stdafx.h"
#include "ControlXml.h"
#include "Markup.h"

using namespace std;

ADTypeTable	     m_ADTypeTable[9];
OthersSetting    m_OthersSetting;
ViewWindows      m_ViewWindows[4];
FormView         m_FormView[20];
DrawView         m_DrawView[20];
//////////////////////////////////////////////////////////////////////////////
// Conversion helper functions

//////////////////////////////////////////////////////////////////////////////
// CControlXml

CControlXml::CControlXml()
{
}

CControlXml::~CControlXml()
{
}

bool CControlXml::ReadFile(const CString& xmlFile, CString& xmlText)
{
    // This code derived from Ben Bryant's MarkupDlg.cpp file.

    // Open file.
    CFile file;
    if ( !file.Open(xmlFile, CFile::modeRead) )
    {
        return false;
    }
    int nFileLen = (int)file.GetLength();

    // Allocate buffer for binary file data.
    unsigned char* pBuffer = new unsigned char[nFileLen + 2];
    nFileLen = file.Read( pBuffer, nFileLen );
    file.Close();
    pBuffer[nFileLen] = '\0';
    pBuffer[nFileLen+1] = '\0'; // in case 2-byte encoded

    // Windows Unicode file is detected if starts with FEFF.
    if ( pBuffer[0] == 0xff && pBuffer[1] == 0xfe )
    {
        // Contains byte order mark, so assume wide char content.
        // Non _UNICODE builds should perform UCS-2 (wide char) to UTF-8 conversion here.
        xmlText = (LPCWSTR)(&pBuffer[2]);
    }
    else
    {
        // _UNICODE builds should perform UTF-8 to UCS-2 (wide char) conversion here.
        xmlText = (LPCSTR)pBuffer;
    }
    delete [] pBuffer;

    // If it is too short, assume it got truncated due to non-text content.
    if ( xmlText.GetLength() < nFileLen / 2 - 20 )
    {
        return false;
    }

    return true;
}

bool CControlXml::ParseXml(const CString xmlFile)
{
    // Read the XML file into a CString.
    CString xmlText;
    if ( !ReadFile(xmlFile, xmlText) )
        return false;

    // Initialize the markup object (parser).
    CMarkup xml;
    xml.SetDoc(xmlText);
    xml.ResetPos();

    // There must be a <ControlWnd> element.
    if ( !xml.FindElem(_T("MDIFrameWnd")) )
        return false;

    // Look for and parse the <ControlGroups> element.
    if ( xml.IntoElem() )
    {            
        while( true )
        {
                // Parse each control group (recursive method).
                if ( !ParseGroups(xml) )
                    break;
        }
        xml.OutOfElem();
    }

    return true;
}

bool CControlXml::ParseGroups(CMarkup& xml)
{
    // Look for <ControlGroups> element.
	if(xml.FindElem(_T("IpAddress")))
	{
    // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("Port"));
		int numForms;
    	m_Str2Data.StringToInteger(strnumForm,numForms);
		m_OthersSetting.Port = numForms;
        strnumForm = xml.GetAttrib(_T("IP"));
		m_OthersSetting.IP = strnumForm;
        return true;
	}
	else if ( xml.FindElem(_T("PointsSetting")) )
    {
    // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("numForms"));
        strnumForm = xml.GetAttrib(_T("Name"));
		m_OthersSetting.DBname = strnumForm;

        if ( xml.IntoElem() )
        {
            while( true )
            {
                // Parse each control group (recursive method).
                if ( !ParsePS(xml) )
                    break;
            }
            xml.OutOfElem();
        }
        return true;
    }
    else if ( xml.FindElem(_T("FormViews")) )
    {
    // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("numForms"));
		int numForms;
    	m_Str2Data.StringToInteger(strnumForm,numForms);
        strnumForm = xml.GetAttrib(_T("Name"));
		m_ViewWindows[numForms].VWName = strnumForm;

        if ( xml.IntoElem() )
        {
			int numw = 0;
            while( true )
            {
                // Parse each control group (recursive method).
                if ( !ParseGroup(xml) )
                    break;
				numw++;
            }
            xml.OutOfElem();
			m_ViewWindows[numForms].numFormView = numw;
        }
        return true;
    }
	else if(xml.FindElem(_T("DrawViews")))
	{
    // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("numForms"));
		int numForms;
    	m_Str2Data.StringToInteger(strnumForm,numForms);
        strnumForm = xml.GetAttrib(_T("Name"));
		m_ViewWindows[numForms].VWName = strnumForm;

        if ( xml.IntoElem() )
        {
			int numw = 0;
            while( true )
            {
                // Parse each control group (recursive method).
                if ( !ParseDrawView(xml) )
                    break;
				numw++;
            }
            xml.OutOfElem();
			m_ViewWindows[numForms].numDrawView = numw;
        }
        return true;
	}
    return false;
}

bool CControlXml::ParseDrawView(CMarkup& xml)
{
    // Look for <ControlGroup> element.
    if ( !xml.FindElem(_T("DrawView")) )
        return false;

    // Extract the group name.
    CString strnumForm = xml.GetAttrib(_T("numForm"));
	m_Str2Data.StringToInteger(strnumForm,numForm);
    CString groupName = xml.GetAttrib(_T("Name"));
	m_DrawView[numForm].DrawViewName = groupName;
    
    return true;
}

bool CControlXml::ParsePS(CMarkup& xml)
{
	LPCTSTR str1 = "",str2 = "",str3 = "";
    // Look for <Controls> element.
    if (xml.FindElem(_T("Analogtype")) )    //模拟量
	{
		// Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("TABLE"));
    	m_ADTypeTable[0].TableName = strnumForm;    
        CString groupName = xml.GetAttrib(_T("Name"));
    	m_ADTypeTable[0].NameD = groupName;

     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn0")),str1,str2,str3);
        m_ADTypeTable[0].m_DTypeTField.DID = str1;
        m_ADTypeTable[0].m_DTypeTField.Name = str2;
        m_ADTypeTable[0].m_DTypeTField.ltop = str3;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn1")),str1,str2,str3);
        m_ADTypeTable[0].m_DTypeTField.lbom = str1;
        m_ADTypeTable[0].m_DTypeTField.palmu = str2;
        m_ADTypeTable[0].m_DTypeTField.palmd = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn2")),str1,str2,str3);
    m_ADTypeTable[0].m_DTypeTField.pbrk = str1;
    m_ADTypeTable[0].m_DTypeTField.prtn = str2;
    m_ADTypeTable[0].m_DTypeTField.punit = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn3")),str1,str2,str3);
    m_ADTypeTable[0].m_DTypeTField.pico = str1;
    m_ADTypeTable[0].m_DTypeTField.falm = str2;
    m_ADTypeTable[0].m_DTypeTField.fdel = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn4")),str1,str2,str3);
    m_ADTypeTable[0].m_DTypeTField.recdate = str1;
    m_ADTypeTable[0].m_DTypeTField.deldate = str2;
    m_ADTypeTable[0].m_DTypeTField.Useridadd = str3;
    strnumForm = xml.GetAttrib(_T("DBColumn5"));
    m_ADTypeTable[0].m_DTypeTField.Useriddel = strnumForm;

	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading0")),str1,str2,str3);
    m_ADTypeTable[0].m_DTypeTFD.Name = str1;
    m_ADTypeTable[0].m_DTypeTFD.punit = str2;
    m_ADTypeTable[0].m_DTypeTFD.ltop = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading1")),str1,str2,str3);
    m_ADTypeTable[0].m_DTypeTFD.lbom = str1;
    m_ADTypeTable[0].m_DTypeTFD.palmu = str2;
    m_ADTypeTable[0].m_DTypeTFD.palmd = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading2")),str1,str2,str3);
    m_ADTypeTable[0].m_DTypeTFD.pbrk = str1;
        m_ADTypeTable[0].m_DTypeTFD.prtn = str2;
        m_ADTypeTable[0].m_DTypeTFD.falm = str3;
      	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading3")),str1,str2,str3);
        m_ADTypeTable[0].m_DTypeTFD.recdate = str1;
        m_ADTypeTable[0].m_DTypeTFD.pico = str2;
        m_ADTypeTable[0].m_DTypeTFD.Useridadd = str3;
        return true;
	}
    else if (xml.FindElem(_T("Digitaltype")) )//开关量
	{
        // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("TABLE"));
    	m_ADTypeTable[1].TableName = strnumForm;
        CString groupName = xml.GetAttrib(_T("Name"));
    	m_ADTypeTable[1].NameD = groupName;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn0")),str1,str2,str3);
        m_ADTypeTable[1].m_DTypeTField.DID = str1;
        m_ADTypeTable[1].m_DTypeTField.Name = str2;
        m_ADTypeTable[1].m_DTypeTField.ptype = str3;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn1")),str1,str2,str3);
        m_ADTypeTable[1].m_DTypeTField.name0 = str1;
        m_ADTypeTable[1].m_DTypeTField.name1 = str2;
        m_ADTypeTable[1].m_DTypeTField.name2 = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn2")),str1,str2,str3);
    m_ADTypeTable[1].m_DTypeTField.palms = str1;
    m_ADTypeTable[1].m_DTypeTField.falm = str2;
    m_ADTypeTable[1].m_DTypeTField.fdel = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn3")),str1,str2,str3);
    m_ADTypeTable[1].m_DTypeTField.recdate = str1;
    m_ADTypeTable[1].m_DTypeTField.deldate = str2;
    m_ADTypeTable[1].m_DTypeTField.Useridadd = str3;
    strnumForm = xml.GetAttrib(_T("DBColumn4"));
    m_ADTypeTable[1].m_DTypeTField.Useriddel = strnumForm;

	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading0")),str1,str2,str3);
    m_ADTypeTable[1].m_DTypeTFD.Name = str1;
    m_ADTypeTable[1].m_DTypeTFD.ptype = str2;
    m_ADTypeTable[1].m_DTypeTFD.name0 = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading1")),str1,str2,str3);
    m_ADTypeTable[1].m_DTypeTFD.name1 = str1;
    m_ADTypeTable[1].m_DTypeTFD.name2 = str2;
    m_ADTypeTable[1].m_DTypeTFD.palms = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading2")),str1,str2,str3);
    m_ADTypeTable[1].m_DTypeTFD.falm = str1;
        m_ADTypeTable[1].m_DTypeTFD.recdate = str2;
        m_ADTypeTable[1].m_DTypeTFD.Useridadd = str3;
        return true;
	}
    else if (xml.FindElem(_T("Pointdescription")) )
	{
        // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("TABLE"));
    	m_ADTypeTable[3].TableName = strnumForm;
        CString groupName = xml.GetAttrib(_T("Name"));
    	m_ADTypeTable[3].NameD = groupName;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn0")),str1,str2,str3);
        m_ADTypeTable[3].m_DTypeTField.DID = str1;
        m_ADTypeTable[3].m_DTypeTField.ptype = str2;
        m_ADTypeTable[3].m_DTypeTField.utype = str3;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn1")),str1,str2,str3);
        m_ADTypeTable[3].m_DTypeTField.typeID = str1;
        m_ADTypeTable[3].m_DTypeTField.positionid = str2;
        m_ADTypeTable[3].m_DTypeTField.fds = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn2")),str1,str2,str3);
    m_ADTypeTable[3].m_DTypeTField.chan = str1;
    m_ADTypeTable[3].m_DTypeTField.subOpr = str2;
    m_ADTypeTable[3].m_DTypeTField.fdel = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn3")),str1,str2,str3);
    m_ADTypeTable[3].m_DTypeTField.recdate = str1;
    m_ADTypeTable[3].m_DTypeTField.deldate = str2;
    m_ADTypeTable[3].m_DTypeTField.Useridadd = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn4")),str1,str2,str3);
    m_ADTypeTable[3].m_DTypeTField.Useriddel = str1;
    m_ADTypeTable[3].m_DTypeTField.pointnum = str2;

	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading0")),str1,str2,str3);
    m_ADTypeTable[3].m_DTypeTFD.ptype = str1;
    m_ADTypeTable[3].m_DTypeTFD.utype = str2;
    m_ADTypeTable[3].m_DTypeTFD.typeID = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading1")),str1,str2,str3);
    m_ADTypeTable[3].m_DTypeTFD.potioinid = str1;
    m_ADTypeTable[3].m_DTypeTFD.fds = str2;
    m_ADTypeTable[3].m_DTypeTFD.chan = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading2")),str1,str2,str3);
    m_ADTypeTable[3].m_DTypeTFD.subOpr = str1;
        m_ADTypeTable[3].m_DTypeTFD.recdate = str2;
        m_ADTypeTable[3].m_DTypeTFD.Useridadd = str3;
	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading3")),str1,str2,str3);
        m_ADTypeTable[3].m_DTypeTFD.Name = str1;
        m_ADTypeTable[3].m_DTypeTFD.pointnum = str2;
        return true;
	}
    else if (xml.FindElem(_T("Fixlocation")) )  //安装地点
	{
        // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("TABLE"));
    	m_ADTypeTable[2].TableName = strnumForm;
        CString groupName = xml.GetAttrib(_T("Name"));
    	m_ADTypeTable[2].NameD = groupName;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("DBColumn0")),str1,str2,str3);
        m_ADTypeTable[2].m_DTypeTField.DID = str1;
        m_ADTypeTable[2].m_DTypeTField.Name = str2;
        strnumForm = xml.GetAttrib(_T("ColumnHeading0"));
        m_ADTypeTable[2].m_DTypeTFD.Name = strnumForm;
        return true;
	}
    else if (xml.FindElem(_T("Dispoint")) )
	{
        // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("TABLE"));
    	m_ADTypeTable[4].TableName = strnumForm;
        CString groupName = xml.GetAttrib(_T("Name"));
    	m_ADTypeTable[4].NameD = groupName;
        strnumForm = xml.GetAttrib(_T("DBColumn0"));
        m_ADTypeTable[4].m_DTypeTField.DID = strnumForm;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading0")),str1,str2,str3);
        m_ADTypeTable[4].m_DTypeTFD.Name = str1;
        m_ADTypeTable[4].m_DTypeTFD.utype = str2;
        m_ADTypeTable[4].m_DTypeTFD.pointnum = str3;
        return true;
	}
    else if (xml.FindElem(_T("Control")) )
	{
        // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("TABLE"));
    	m_ADTypeTable[5].TableName = strnumForm;
        CString groupName = xml.GetAttrib(_T("Name"));
    	m_ADTypeTable[5].NameD = groupName;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading0")),str1,str2,str3);
        m_ADTypeTable[5].m_DTypeTFD.Name = str1;
        m_ADTypeTable[5].m_DTypeTFD.pointnum = str2;
        m_ADTypeTable[5].m_DTypeTFD.chan = str3;
     	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading1")),str1,str2,str3);
        m_ADTypeTable[5].m_DTypeTFD.falm = str1;
        m_ADTypeTable[5].m_DTypeTFD.recdate = str2;
        m_ADTypeTable[5].m_DTypeTFD.Useridadd = str3;
        return true;
	}
    else if (xml.FindElem(_T("Specialcontrol")) )
	{
        // Extract the group name.
        CString strnumForm = xml.GetAttrib(_T("TABLE"));
    	m_ADTypeTable[6].TableName = strnumForm;
        CString groupName = xml.GetAttrib(_T("Name"));
    	m_ADTypeTable[6].NameD = groupName;
        strnumForm = xml.GetAttrib(_T("ColumnHeading0"));
        m_ADTypeTable[6].m_DTypeTFD.Name = strnumForm;
        return true;
	}
    

	return false;
}

bool CControlXml::ParseGroup(CMarkup& xml)
{
    // Look for <ControlGroup> element.
    if ( !xml.FindElem(_T("FormView")) )
        return false;

    // Extract the group name.
    CString strnumForm = xml.GetAttrib(_T("numForm"));
    if ( strnumForm.IsEmpty() )
        return false;
	m_Str2Data.StringToInteger(strnumForm,numForm);
//	m_FormView[numForm].numForm = numForm;

    CString groupName = xml.GetAttrib(_T("Name"));
    if ( groupName.IsEmpty() )
        return false;
	m_FormView[numForm].FormViewName = groupName;
    
    // See if this control group has any controls.
    if ( xml.IntoElem() )
    {
            while( true )
            {
                // Parse each control group (recursive method).
                if ( !ParseControls(xml) )
                    break;
            }
        xml.OutOfElem();
    }

    // See if this control group has any child groups.
    if ( xml.IntoElem() )
    {
        ParseGroups(xml);
        xml.OutOfElem();
    }

    return true;
}

bool CControlXml::ParseControls(CMarkup& xml)
{
	bool bVisible;
	int  intVisible;
    int b0 = 0, b1 = 0, b2 = 0;
	LPCTSTR str1 = "",str2 = "",str3 = "";
    // Look for <Controls> element.
    if ( !xml.FindElem(_T("ListCtrl")) )
        return false;

    // Extract the group name.
    CString strnumForm = xml.GetAttrib(_T("numList"));
    if ( strnumForm.IsEmpty() )
        return false;
	m_Str2Data.StringToInteger(strnumForm,numList);
//	m_FormView[numForm].m_ListCtrl[numList] = numForm;

    strnumForm = xml.GetAttrib(_T("Visible"));
	m_Str2Data.StringToBool(strnumForm,bVisible);
	m_FormView[numForm].m_ListCtrl[numList].Visible = bVisible;
    strnumForm = xml.GetAttrib(_T("SubclassHeader"));
	m_Str2Data.StringToBool(strnumForm,bVisible);
	m_FormView[numForm].m_ListCtrl[numList].SubclassHeader = bVisible;

	m_Str2Data.StringToInteger(xml.GetAttrib(_T("MoveWindowx")),intVisible);
	m_FormView[numForm].m_ListCtrl[numList].MoveWindowx = intVisible;
	m_Str2Data.StringToInteger(xml.GetAttrib(_T("SetWindowPosX")),intVisible);
	m_FormView[numForm].m_ListCtrl[numList].SetWindowPosX = intVisible;
	m_Str2Data.StringToInteger(xml.GetAttrib(_T("SetWindowPosY")),intVisible);
	m_FormView[numForm].m_ListCtrl[numList].SetWindowPosY = intVisible;

	m_Str2Data.SplittoCString(xml.GetAttrib(_T("ColumnHeading")),str1,str2,str3);
    m_FormView[numForm].m_ListCtrl[numList].ColumnHeading1 = str1;
    m_FormView[numForm].m_ListCtrl[numList].ColumnHeading2 = str2;
    m_FormView[numForm].m_ListCtrl[numList].ColumnHeading3 = str3;

	m_Str2Data.Splittoint(xml.GetAttrib(_T("ColumnWidth")),b0,b1,b2);
    m_FormView[numForm].m_ListCtrl[numList].ColumnWidth1 = b0;
    m_FormView[numForm].m_ListCtrl[numList].ColumnWidth2 = b1;
    m_FormView[numForm].m_ListCtrl[numList].ColumnWidth3 = b2;

	m_Str2Data.StringToInteger(xml.GetAttrib(_T("ColumniItem")),intVisible);
	m_FormView[numForm].m_ListCtrl[numList].ColumniItem = intVisible;

	m_Str2Data.Splittoint(xml.GetAttrib(_T("BackColor")),b0,b1,b2);
	m_FormView[numForm].m_ListCtrl[numList].BackColor = RGB(b0,b1,b2);

	m_Str2Data.Splittoint(xml.GetAttrib(_T("TextColor")),b0,b1,b2);
	m_FormView[numForm].m_ListCtrl[numList].TextColor = RGB(b0,b1,b2);

	m_Str2Data.Splittoint(xml.GetAttrib(_T("AlarmTextColor")),b0,b1,b2);
	m_FormView[numForm].m_ListCtrl[numList].AlarmTextColor = RGB(b0,b1,b2);

	m_Str2Data.Splittoint(xml.GetAttrib(_T("AlarmBackColor")),b0,b1,b2);
	m_FormView[numForm].m_ListCtrl[numList].AlarmBackColor = RGB(b0,b1,b2);

    return true;
}



/*
void CControlXml::ParseControl_Common(CMarkup& xml, CWndControl* pControl)
{
    bool   flag;
    CPoint location;
    CSize  size;

    pControl->SetName(xml.GetAttrib(_T("Name")));        

    if ( StringToBool(xml.GetAttrib(_T("Visible")), flag) )
        pControl->SetVisible(flag);

    if ( StringToBool(xml.GetAttrib(_T("Enabled")), flag) )
        pControl->SetEnabled(flag);    

    if ( StringToBool(xml.GetAttrib(_T("ReadOnly")), flag) )
        pControl->SetReadOnly(flag);   
   
    if ( StringToLocation(xml.GetAttrib(_T("LocationX")), xml.GetAttrib(_T("LocationY")), location) )
        pControl->SetLocation(location);

    if ( StringToSize(xml.GetAttrib(_T("SizeWidth")), xml.GetAttrib(_T("SizeHeight")), size) )
        pControl->SetSize(size);
}

void CControlXml::PerformLinking(CMarkup& xml)
{
    // Only radio buttons use linking for now.
    if ( pControl->GetTypeName() == _T("RadioButton") )
    {
        // Get the radio manager name.
        CString managerName = xml.GetAttrib(_T("RadioManager"));
        if ( !managerName.IsEmpty() )
        {
            // Look in the control list for a radio button with this manager name.
            list<CWndControl*>::iterator iter = controlList.begin();
            for( ; iter != controlList.end(); ++iter)
            {
                CWndControl* pLinkFrom = *iter;
                if ( pLinkFrom->GetTypeName() == _T("RadioButton") &&
                     pLinkFrom->GetName() == managerName )
                {
                    // Set up the linking.
                    pLinkFrom->AddLinkedControl(pControl);
                }
            }
        }
    }
}
/*
CWndControl* CControlXml::ParseControl_Button(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndButton* pControl = static_cast<CWndButton*>(controlFactory->CreateControl(_T("Button")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse button-specific attributes.
    pControl->SetText(xml.GetAttrib(_T("Text")));

    return pControl;
}

CWndControl* CControlXml::ParseControl_CheckBox(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndCheckBox* pControl = static_cast<CWndCheckBox*>(controlFactory->CreateControl(_T("CheckBox")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse checkbox-specific attributes.
    pControl->SetText(xml.GetAttrib(_T("Text")));

    bool checked;
    if ( StringToBool(xml.GetAttrib(_T("Checked")), checked) )
        pControl->SetChecked(checked);        

    return pControl;
}

CWndControl* CControlXml::ParseControl_ComboBox(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndComboBox* pControl = static_cast<CWndComboBox*>(controlFactory->CreateControl(_T("ComboBox")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse combobox-specific attributes.        
    list<CString> itemList;
    if ( StringToItems(xml.GetAttrib(_T("Items")), itemList) )
        pControl->AddItems(itemList);        

    int val;
    if ( StringToInteger(xml.GetAttrib(_T("SelectedIndex")), val) )
        pControl->SetSelectedIndex(val);

    return pControl;
}

CWndControl* CControlXml::ParseControl_GroupBox(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndGroupBox* pControl = static_cast<CWndGroupBox*>(controlFactory->CreateControl(_T("GroupBox")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse groupbox-specific attributes.
    pControl->SetText(xml.GetAttrib(_T("Text")));

    return pControl;
}

CWndControl* CControlXml::ParseControl_IpAddress(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndIpAddress* pControl = static_cast<CWndIpAddress*>(controlFactory->CreateControl(_T("IpAddress")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse ipaddress-specific attributes.
    pControl->SetIpAddress(xml.GetAttrib(_T("IP")));

    return pControl;
}

CWndControl* CControlXml::ParseControl_Label(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndLabel* pControl = static_cast<CWndLabel*>(controlFactory->CreateControl(_T("Label")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse label-specific attributes.
    pControl->SetText(xml.GetAttrib(_T("Text")));

    return pControl;
}

CWndControl* CControlXml::ParseControl_ListBox(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndListBox* pControl = static_cast<CWndListBox*>(controlFactory->CreateControl(_T("ListBox")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse listbox-specific attributes.       
    list<CString> itemList;
    if ( StringToItems(xml.GetAttrib(_T("Items")), itemList) )
        pControl->AddItems(itemList);        

    int val;
    if ( StringToInteger(xml.GetAttrib(_T("SelectedIndex")), val) )
        pControl->SetSelectedIndex(val);

    return pControl;
}

CWndControl* CControlXml::ParseControl_RadioButton(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndRadioButton* pControl = static_cast<CWndRadioButton*>(controlFactory->CreateControl(_T("RadioButton")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse radiobutton-specific attributes.
    pControl->SetText(xml.GetAttrib(_T("Text")));

    bool checked;
    if ( StringToBool(xml.GetAttrib(_T("Checked")), checked) )
        pControl->SetChecked(checked);

    return pControl;
}

CWndControl* CControlXml::ParseControl_SpinButton(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndSpinButton* pControl = static_cast<CWndSpinButton*>(controlFactory->CreateControl(_T("SpinButton")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse spinbutton-specific attributes.       
    int val;
    if ( StringToInteger(xml.GetAttrib(_T("Minimum")), val) )
        pControl->SetMinimum(val);

    if ( StringToInteger(xml.GetAttrib(_T("Maximum")), val) )
        pControl->SetMaximum(val);        

    if ( StringToInteger(xml.GetAttrib(_T("Value")), val) )
        pControl->SetValue(val);

    return pControl;
}

CWndControl* CControlXml::ParseControl_TextBox(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndTextBox* pControl = static_cast<CWndTextBox*>(controlFactory->CreateControl(_T("TextBox")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse textbox-specific attributes.
    pControl->SetText(xml.GetAttrib(_T("Text")));

    return pControl;
}

CWndControl* CControlXml::ParseControl_TrackBar(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndTrackBar* pControl = static_cast<CWndTrackBar*>(controlFactory->CreateControl(_T("TrackBar")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse trackbar-specific attributes.
    int val;
    if ( StringToInteger(xml.GetAttrib(_T("Minimum")), val) )
        pControl->SetMinimum(val);

    if ( StringToInteger(xml.GetAttrib(_T("Maximum")), val) )
        pControl->SetMaximum(val);        

    if ( StringToInteger(xml.GetAttrib(_T("TickFrequency")), val) )
        pControl->SetTickFrequency(val);

    if ( StringToInteger(xml.GetAttrib(_T("Value")), val) )
        pControl->SetValue(val);

    return pControl;
}

CWndControl* CControlXml::ParseControl_WebBrowser(CMarkup& xml, CWndFactory* controlFactory)
{
    // Create control.
    CWndWebBrowser* pControl = static_cast<CWndWebBrowser*>(controlFactory->CreateControl(_T("WebBrowser")));

    // Read attribute values from XML and use to set control.
    ParseControl_Common(xml, pControl);       
    
    // Parse webbrowser-specific attributes.
    pControl->SetUrl(xml.GetAttrib(_T("Url")));

    return pControl;
}
*/
// END

