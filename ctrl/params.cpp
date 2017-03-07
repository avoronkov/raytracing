#include "params.h"

#include <QtMath>

namespace rt { namespace ctrl {

Params::Params():
    TG_15{qTan(M_PI * 15.0 / 180)}
{
    offset = 10;
    r = 0.01;
    d = 0.1;
    flag_raster_modified = false;
    m_width = 240;
    m_height = 240;
    flag_doc_opeded = false;
    flag_colorful = false;
    flag_render_in_process = false;
    flag_render_ready = false;
}

}}
