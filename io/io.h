#ifndef IO_H
#define IO_H

#include <QFile>
#include <QTextStream>

#include "model/scene.h"

namespace rt { namespace io {

bool loadSceneFile(QFile *, rt::model::Scene *);
bool loadSceneStream(QTextStream *, rt::model::Scene *);




}}

#endif // IO_H
