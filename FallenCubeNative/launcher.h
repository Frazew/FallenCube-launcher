#ifndef LAUNCHER
#define LAUNCHER
class Launcher
{
public:

    Launcher();

    QString name() const;
    void setName(const QString &name);

    int level() const;
    void setLevel(int level);

    ClassType classType() const;
    void setClassType(ClassType classType);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
private:
    QString mName;
    int mLevel;
    ClassType mClassType;
};
#endif // LAUNCHER

