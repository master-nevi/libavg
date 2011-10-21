//
//  libavg - Media Playback Engine. 
//  Copyright (C) 2003-2011 Ulrich von Zadow
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  Current versions can be found at www.libavg.de
//

#include "ShadowFXNode.h"

#include "../base/ObjectCounter.h"
#include "../base/Exception.h"
#include "../graphics/ShaderRegistry.h"

#include <string>

using namespace std;

namespace avg {

ShadowFXNode::ShadowFXNode() 
    : FXNode(),
      m_Offset(0,0),
      m_StdDev(1),
      m_Opacity(1),
      m_Color(255,255,255,255)
{
    ObjectCounter::get()->incRef(&typeid(*this));
    if (!GLTexture::isFloatFormatSupported()) {
        throw Exception(AVG_ERR_UNSUPPORTED, 
                "OpenGL configuration doesn't support Shadow (no float textures).");
    }
}

ShadowFXNode::~ShadowFXNode()
{
    ObjectCounter::get()->decRef(&typeid(*this));
}

void ShadowFXNode::connect()
{
    if (!GLTexture::isFloatFormatSupported()) {
        throw Exception(AVG_ERR_UNSUPPORTED, 
                "Cannot create ShadowFX: OpenGL configuration doesn't support Blur (no float textures).");
    }
    FXNode::connect();
}

void ShadowFXNode::disconnect()
{
    m_pFilter = GPUShadowFilterPtr();
    FXNode::disconnect();
}

void ShadowFXNode::setParams(const DPoint& offset, double stdDev, double opacity, 
        const string& sColor)
{
    m_Offset = offset;
    m_StdDev = stdDev;
    m_Opacity = opacity;
    m_sColorName = sColor;
    m_Color = colorStringToColor(sColor);
    updateFilter();
}
    
void ShadowFXNode::setOffset(const DPoint& offset)
{
    m_Offset = offset;
    updateFilter();
}

DPoint ShadowFXNode::getOffset() const
{
    return m_Offset;
}

void ShadowFXNode::setRadius(double radius)
{
    m_StdDev = radius;
    updateFilter();
}

double ShadowFXNode::getRadius() const
{
    return m_StdDev;
}

void ShadowFXNode::setOpacity(double opacity)
{
    m_Opacity = opacity;
    updateFilter();
}

double ShadowFXNode::getOpacity() const
{
    return m_Opacity;
}

void ShadowFXNode::setColor(const std::string& sColor)
{
    m_sColorName = sColor;
    m_Color = colorStringToColor(sColor);
    updateFilter();
}

std::string ShadowFXNode::getColor() const
{
    return m_sColorName;
}

GPUFilterPtr ShadowFXNode::createFilter(const IntPoint& size)
{
    m_pFilter = GPUShadowFilterPtr(new GPUShadowFilter(size, m_Offset, m_StdDev, 
            m_Opacity, m_Color));
    setDirty();
    return m_pFilter;
}

void ShadowFXNode::updateFilter()
{
    if (m_pFilter) {
        m_pFilter->setParams(m_Offset, m_StdDev, m_Opacity, m_Color);
        setDirty();
    }
}

}

