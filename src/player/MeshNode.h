//
//  libavg - Media Playback Engine. 
//  Copyright (C) 2003-2008 Ulrich von Zadow
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


#ifndef _MeshNode_H_
#define _MeshNode_H_

#include "../api.h"
#include "VectorNode.h"
#include "../graphics/Pixel32.h"
#include "../base/IntTriple.h"
#include <vector>

namespace avg {

class AVG_API MeshNode : public VectorNode
{
    public:
        static NodeDefinition createDefinition();
        
        MeshNode(const ArgList& Args);
        virtual ~MeshNode();
        
        void isValid(const std::vector<DPoint>& coords);

        const std::vector<DPoint>& getVertexCoords() const;
        void setVertexCoords(const std::vector<DPoint>& coords);

        const std::vector<DPoint>& getTexCoords() const;
        void setTexCoords(const std::vector<DPoint>& coords);

        const std::vector<IntTriple>& getTriangles() const;
        void setTriangles(const std::vector<IntTriple>& pts);

        virtual int getNumVertexes();
        virtual int getNumIndexes();
        virtual void calcVertexes(VertexArrayPtr& pVertexArray, Pixel32 color);

    private:
        std::vector<DPoint> m_TexCoords;
        std::vector<DPoint> m_VertexCoords;
        std::vector<IntTriple> m_Triangles;
};
}
#endif
