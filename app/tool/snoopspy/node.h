#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QPainter>

#include <VStateObject>

#include "arrow.h"

class Node : public QGraphicsTextItem
{
public:
  enum { Type = UserType + 5 };
  int type() const { return Type; }

public:
  Node(VStateObject* object);
  virtual ~Node();

public:
  QList<Arrow *> arrows;
  void addArrow(Arrow *arrow);
  void removeArrow(Arrow *arrow);
  void removeArrows();

public:
  VStateObject* object; // reference

public:
  // virtual QRectF boundingRect() const; //
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // NODE_H
