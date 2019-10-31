// file: ./src/libs/exe/ApplicationSettings.h

#include <QObject>

#include <QList>
#include <QSettings>
#include <QStack>
#include <QString>
#include <QVariant>

class ApplicationSettings : public QObject
{
    Q_OBJECT
public:
    typedef QString LayerName;   // TODO BasicName
    typedef QList<LayerName> LayerNameList;
    typedef int Layer;           // TODO Index
    typedef QList<Layer> LayerList;
    typedef QString Key;         // TODO BasicId
    typedef QVariant Value;
//********SettingssOURCE
    class SettingsSource
    {
        SettingsSource(void);
    };
//********^SettingsSource

public:
    explicit ApplicationSettings(QObject * parent=nullptr);
    bool contains(const Key & key, const int maxLayers=-1);
    bool layerContains(const Key & key, const int layer=0);
    Layer whichLayerContains(const Key & key);
    Layer layerFromName(const LayerName & layerName);
    LayerName layerName(const Layer layer);
    LayerName whichLayerNameContains(const Key & key);
    Value value(const Key & key, const Layer maxLayers=-1);
    Value valueAtLayer(const Key & key, const Layer layer=0);
    Value valueAtLayer(const Key & key, const LayerName layerName);


public slots:
//    void push(const SettingsSource & source)        {;} // TODO
//    void set(const Key & key, const Value & value)        {;} // TODO: top-pop layer
//    void setAt(const Layer layer, const Key & key, const Value & value) {;}
//    void setAt(const LayerName layerName, const Key & key, const Value & value) {;}
//    void scan(LayerList layerList=LayerList()) {;} // TODO

signals:
    void initialStart(Layer, LayerName);
    void initialFinish(Layer, LayerName);
    void initial(Layer, LayerName, Value);
    void valueSet(Layer, LayerName, Value newValue, Value oldValue);
    void scanStart(LayerList, LayerNameList);


protected:
//********SettingsLayer
    class SettingsLayer : public QSettings
    {
    public:

    public:
        SettingsLayer(const LayerName & layerName,
                      QObject * parent=nullptr);
        LayerName layerName(void) const;

    private:
        LayerName cmName;



    }; // Layer sub-class
//******^SettingsLayer

protected slots:

signals:

private:
    QStack<SettingsLayer *> mLayerStack;

};

