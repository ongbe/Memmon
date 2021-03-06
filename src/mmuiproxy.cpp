#include "mmuiproxy.h"
#include "../ctrl/searchedit.h"


MmUiProxy::MmUiProxy(Memmon *parent) :
    QObject((QWidget*)parent),_parent(parent)
{
    initWidgets();
    initLabels();
    initActions();
    initMenus();
    initToolBars();
    initComboBoxes();
    initSpinBoxes();
    initToolButtons();
}

void MmUiProxy::initWidgets()
{
    PYProg* cpuProg = new PYProg((QWidget*)_parent);
    cpuProg->setToolTip("CPU Usage");
    cpuProg->setAnimated(true);
    ADD_WIDGET(Widget,Widget_CpuIndicator,cpuProg)

    PYProg* memProg = new PYProg((QWidget*)_parent);
    memProg->setToolTip("Memory Usage");
    memProg->setAnimated(true);
    ADD_WIDGET(Widget,Widget_MemIndicator,memProg)

    PYHistory* cpuHistory = new PYHistory((QWidget*)_parent);
    ADD_WIDGET(Widget,Widget_CpuUsageHistory,cpuHistory)

    PYHistory* memHistory = new PYHistory((QWidget*)_parent);
    ADD_WIDGET(Widget,Widget_MemUsageHistory,memHistory)

    SearchEdit* searchEdit = new SearchEdit((QWidget*)_parent);
    ADD_WIDGET(Widget,Widget_SearchEdit,searchEdit)
}

void MmUiProxy::initLabels()
{
    ADD_WIDGET(Label,Label_Status,createLabel(MM::Text::Empty))
    ADD_WIDGET(Label,Label_UpdateInterval,createLabel(MM::Text::Label_UpdateInterval))
    ADD_WIDGET(Label,Label_TotalProcessCount,createLabel(MM::Text::Empty))
    ADD_WIDGET(Label,Label_RunningServiceCount,createLabel(MM::Text::Empty))
    ADD_WIDGET(Label,Label_RunningDriverCount,createLabel(MM::Text::Empty))
    ADD_WIDGET(Label,Label_SearchEditPrompt,createLabel(MM::Text::Label_Search))
    ADD_WIDGET(Label,Label_DataCountPrompt,createLabel(MM::Text::Label_DataCount))
}

void MmUiProxy::initActions()
{
    ADD_WIDGET(Action,Action_Export,createAction(MM::Text::Action_Export,QIcon(MM::Icon::ExportImage)));
    ADD_WIDGET(Action,Action_Exit,createAction(MM::Text::Action_Exit,QIcon(MM::Icon::Close)));
    ADD_WIDGET(Action,Action_SelectColumns,createAction(MM::Text::SelectColumn,QIcon(MM::Icon::SelectColumn)));
    ADD_WIDGET(Action,Action_Win32_Process,createAction(MM::Text::Win32_Process));
    ADD_WIDGET(Action,Action_Win32_PerfFormattedData_PerfProc_Process,createAction(MM::Text::Win32_PerfFormattedDataPerfProc_Process));
    ADD_WIDGET(Action,Action_MemUtil,createAction(MM::Text::Action_MemoryUtility));
    ADD_WIDGET(Action,Action_LogDock,createAction(MM::Text::Action_QueryLog));
    ADD_WIDGET(Action,Action_WmiQuery,createAction(MM::Text::Action_WmiQuery));
    ADD_WIDGET(Action,Action_Help,createAction(MM::Text::Action_Help));
    ADD_WIDGET(Action,Action_AboutThis,createAction(MM::Text::Action_AboutThis));
    ADD_WIDGET(Action,Action_TakeSnapshot,createAction(MM::Text::Action_TakeSnapshot,QIcon(MM::Icon::Snapshot)));
    ADD_WIDGET(Action,Action_ShowModuleList,createAction(MM::Text::Action_ModuleList,QIcon(MM::Icon::Module)));

    makeActionCheckable(Action_SelectColumns);
    makeActionCheckable(Action_Win32_Process);
    makeActionCheckable(Action_Win32_PerfFormattedData_PerfProc_Process);
    makeActionCheckable(Action_ShowModuleList);
}

void MmUiProxy::initMenus()
{
    ADD_WIDGET(Menu,Menu_File,createMenu(MM::Text::Menu_File))
    ADD_WIDGET(Menu,Menu_Config,createMenu(MM::Text::Menu_Config))
    ADD_WIDGET(Menu,Menu_QueryEngine,createMenu(MM::Text::Menu_SwitchQueryEngine))
    ADD_WIDGET(Menu,Menu_Tools,createMenu(MM::Text::Menu_Tools))
    ADD_WIDGET(Menu,Menu_Window,createMenu(MM::Text::Menu_Window))
    ADD_WIDGET(Menu,Menu_About,createMenu(MM::Text::Menu_About))
}

void MmUiProxy::initToolBars()
{
    ADD_WIDGET(ToolBar,ToolBar_Tool,createToolBar(MM::Text::ToolBar_Tool))
}

void MmUiProxy::initComboBoxes()
{
    ADD_WIDGET(ComboBox,ComboBox_UpdateInterval,createComboBox())
}

void MmUiProxy::initToolButtons()
{
    ADD_WIDGET(ToolButton,ToolButton_Start,createToolButton(MM::Text::TB_StartQuery,QIcon(MM::Icon::StartQuery)))
    ADD_WIDGET(ToolButton,ToolButton_Stop,createToolButton(MM::Text::TB_StopQuery,QIcon(MM::Icon::StopQuery)))
    ADD_WIDGET(ToolButton,ToolButton_Clear,createToolButton(MM::Text::TB_ClearHistoryData,QIcon(MM::Icon::Clear)))
    ADD_WIDGET(ToolButton,ToolButton_ShowPopup,createToolButton(MM::Text::TB_ShowPopupChart,QIcon(MM::Icon::Chart)))
    ADD_WIDGET(ToolButton,ToolButton_GeneralInfo,createToolButton(MM::Text::TB_GeneralInfo,QIcon(MM::Icon::GeneralInfo)))
}

void MmUiProxy::initSpinBoxes()
{
    ADD_WIDGET(SpinBox,SpinBox_DataCount,createSpinBox())
}

void MmUiProxy::makeActionCheckable(Action act)
{
    getAction(act)->setCheckable(true);
}

QMenu* MmUiProxy::createMenu(const QString &strTitle, const QIcon& icon)
{
    PYMenu* menu = new PYMenu((QWidget*)_parent);
    menu->setIcon(icon);
    menu->setTitle(strTitle);
    return menu;
}

QToolBar* MmUiProxy::createToolBar(const QString &strTitle)
{
    QToolBar* bar = new QToolBar((QWidget*)_parent);
    bar->setWindowTitle(strTitle);
    return bar;
}

QAction* MmUiProxy::createAction(const QString &strText,const QIcon &icon, const QString &strShortcut, bool checkable)
{
    QAction* act = new QAction((QWidget*)_parent);
    act->setText(strText);
    act->setIcon(icon);
    act->setShortcut(strShortcut);
    act->setCheckable(checkable);
    connect(act,SIGNAL(triggered()),(QWidget*)_parent,SLOT(slot_actionHandler()));
    return act;
}

QAction* MmUiProxy::createAction(const QString &strText, bool checkable)
{
    QAction* act = new QAction((QWidget*)_parent);
    act->setText(strText);
    act->setCheckable(checkable);
    connect(act,SIGNAL(triggered()),(QWidget*)_parent,SLOT(slot_actionHandler()));
    return act;
}

QPushButton* MmUiProxy::createPushButton(const QString &strText, const QIcon& icon)
{
    QPushButton* button = new QPushButton((QWidget*)_parent);
    button->setText(strText);
    button->setIcon(icon);
    return button;
}

QLabel* MmUiProxy::createLabel(const QString &strText)
{
    QLabel* label = new QLabel((QWidget*)_parent);
    label->setText(strText);
    return label;
}

QComboBox* MmUiProxy::createComboBox()
{
    QComboBox* box = new QComboBox((QWidget*)_parent);
    return box;
}

QSpinBox* MmUiProxy::createSpinBox()
{
    QSpinBox* box = new QSpinBox((QWidget*)_parent);
    box->setRange(10,1000);
    return box;
}

QLineEdit* MmUiProxy::createLineEdit()
{
    QLineEdit* edit = new QLineEdit((QWidget*)_parent);
    return edit;
}

QTimer* MmUiProxy::createTimer(int interval, bool singleShot)
{
    QTimer* timer = new QTimer((QWidget*)_parent);
    timer->setInterval(interval);
    timer->setSingleShot(singleShot);
    return timer;
}

QToolButton* MmUiProxy::createToolButton(const QString &strText, const QIcon &icon)
{
    QToolButton* button = new QToolButton((QWidget*)_parent);
    button->setText(strText);
    button->setAutoRaise(true);
    button->setAutoRepeat(true);
    button->setIcon(icon);
    connect(button,SIGNAL(clicked()),(QWidget*)_parent,SLOT(slot_toolbuttonHandler()));
    return button;
}
