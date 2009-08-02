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

#ifndef _SimpleAnim_H_
#define _SimpleAnim_H_

#include "../api.h"
// Python docs say python.h should be included before any standard headers (!)
#include "../player/WrapPython.h" 

#include "../base/IFrameListener.h"
#include "../player/Node.h"

#include <boost/python.hpp>

#include <string>
#include <map>

namespace avg {

struct ObjAttrID {
    ObjAttrID(const boost::python::object& node, const std::string& sAttrName)
        : m_Node(node),
          m_sAttrName(sAttrName)
    {
    }
    boost::python::object m_Node;
    std::string m_sAttrName;
    bool operator < (const ObjAttrID& other) const;
};

class AVG_API SimpleAnim: public IFrameListener {
public:
    static int getNumRunningAnims();

    SimpleAnim(const boost::python::object& node, const std::string& sAttrName,
            double duration, bool bUseInt, 
            const boost::python::object& startCallback, 
            const boost::python::object& stopCallback);
    virtual ~SimpleAnim()=0;

    void setStartCallback(const boost::python::object& startCallback);
    void setStopCallback(const boost::python::object& stopCallback);
    void start(bool bKeepAttr=false);
    void abort();
    bool isRunning();

    void onFrameEnd();

protected:
    double getStartTime();
    double getDuration();
    void setValue(const boost::python::object& val);

    virtual void step();
    virtual void regularStop()=0;
    virtual void calcStartTime()=0;
    void remove();
    
private:
    boost::python::object m_Node;
    std::string m_sAttrName;
    long long m_Duration;
    bool m_bUseInt;
    boost::python::object m_StartCallback;
    boost::python::object m_StopCallback;
    bool m_bRunning;
    long long m_StartTime;

    typedef std::map<ObjAttrID, SimpleAnim*> AttrAnimationMap;
    static AttrAnimationMap s_ActiveAnimations;
    static void abortAnim(const boost::python::object& node, 
            const std::string& sAttrName);
};

}

#endif 



