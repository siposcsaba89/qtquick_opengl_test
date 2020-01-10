#ifndef FBITEMRENDERER_H
#define FBITEMRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QQuickWindow>
#include <iostream>

class FbItemRenderer : public QQuickFramebufferObject::Renderer
{
public:

    FbItemRenderer(const qreal & blue_val_) : blue_val(blue_val_)
    {

    }


    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
    {
        std::cout << size.width() << " " << size.height() << std::endl;
        QOpenGLFramebufferObjectFormat format;

        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

        // optionally enable multisampling by doing format.setSamples(4);

        return new QOpenGLFramebufferObject(size, format);

    }
    void render()
    {
        std::cout << "render" << std::endl;
        // Called with the FBO bound and the viewport set.

        // Issue OpenGL commands.
        glClearColor(1.0f,blue_val,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.0f,0.0f,0.0f,1.0f);
        m_item->resetOpenGLState();

    }
    const qreal & blue_val;
    QQuickWindow * m_item = nullptr;
};


class FbItem : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    QQuickFramebufferObject::Renderer *createRenderer() const override
    {
        std::cout << "renderer create!" << std::endl;
        FbItemRenderer * r = new FbItemRenderer(blue_val);
        r->m_item = this->window();
        return r;
    }

    Q_INVOKABLE void changeBlue(qreal value)
    {
        std::cout << value << std::endl;
        blue_val = value / 255.0f;
        std::cout << blue_val << std::endl;
        update();
    }
    qreal blue_val;
};

#endif // FBITEMRENDERER_H
