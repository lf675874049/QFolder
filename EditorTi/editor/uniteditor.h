#ifndef UNITEDITOR_H
#define UNITEDITOR_H

#include <QMainWindow>

namespace Ui {
class UnitEditor;
}

class UnitEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit UnitEditor(QWidget *parent = 0);
    ~UnitEditor();

private:
    Ui::UnitEditor *ui;

    /*
    // 编辑区使能, isNew == true 时，右侧填充初始值
    void setEditorEnable(bool isNew = false);

    // 编辑区使能关闭
    void setEditorDisable();

    // 编辑区填充默认值
    // isForce为 true时，所有值恢复为默认值
    // isForce为 false时，检测当前位置是否有非默认值的值 有则保留
    void setEditorDefaultValues(bool isForce);

        // 此处考虑用轻量数据库来维护编辑数据
        // 生成配置文件导出为XML
        // 这样编辑器可以用比较好的时间和内存效率来维护多个版本的资源
        // 选择需求的内容来生成对应的配表项目即可

    // 加载或刷新时调用，加载配表文件生成列表
    void loadFileData();
    // 将内存数据写入到文件
    void writeToFile();
    */
};

#endif // UNITEDITOR_H
