//
//  ofxGPC.h
//
//  Created by satcy on 2/2/15.
//
//

#pragma once

#include "ofMain.h"
#include "gpc.c"

namespace ofx { namespace gpc {
    enum opType{
        DIFF = GPC_DIFF,
        INT = GPC_INT,
        XOR = GPC_XOR,
        UNION = GPC_UNION,
    };
    
    
    inline gpc_polygon ofToGpc(ofPolyline & pl){
        gpc_polygon a;
        a.num_contours = 1;
        a.hole = NULL;
        a.contour = NULL;
        
        MALLOC(a.hole, a.num_contours * sizeof(int), "contour hole", int);
        MALLOC(a.contour, a.num_contours * sizeof(gpc_vertex_list), "contour", gpc_vertex_list);
        
        vector<ofPoint> verts = pl.getVertices();
        int num = verts.size();
        
        gpc_vertex_list g_verts;
        g_verts.num_vertices = num;
        MALLOC(g_verts.vertex, num * sizeof(gpc_vertex), "vertex", gpc_vertex);
        
        for ( int j=0; j<num; j++ ) {
            gpc_vertex g_vec;
            g_vec.x = verts[j].x;
            g_vec.y = verts[j].y;
            
            g_verts.vertex[j] = g_vec;
        }
        
        a.hole[0] = FALSE;
        a.contour[0] = g_verts;
        
        return a;
    }
    
    inline gpc_polygon ofToGpc(ofPath & p){
        vector<ofPolyline> lines = p.getOutline();
        gpc_polygon a;
        a.num_contours = lines.size();
        a.hole = NULL;
        a.contour = NULL;
        
        MALLOC(a.hole, a.num_contours * sizeof(int), "contour hole", int);
        MALLOC(a.contour, a.num_contours * sizeof(gpc_vertex_list), "contour", gpc_vertex_list);
        
        for ( int i=0; i<lines.size(); i++ ) {
            ofPolyline & pl = lines[i];
            if ( !pl.isClosed() ) {
                pl.close();
            }
            vector<ofPoint> verts = pl.getVertices();
            int num = verts.size();
            
            gpc_vertex_list g_verts;
            g_verts.num_vertices = num;
            MALLOC(g_verts.vertex, num * sizeof(gpc_vertex), "vertex", gpc_vertex);
            
            for ( int j=0; j<num; j++ ) {
                gpc_vertex g_vec;
                g_vec.x = verts[j].x;
                g_vec.y = verts[j].y;
                
                g_verts.vertex[j] = g_vec;
            }
            
            a.hole[i] = FALSE;
            a.contour[i] = g_verts;
            
        }
        
        return a;
    }
    
    inline vector<ofPolyline> gpcToOf(gpc_polygon p){
        vector<ofPolyline> res;
        for ( int i=0; i<p.num_contours; i++ ) {
            ofPolyline pl;
            for ( int j=0; j<p.contour[i].num_vertices; j++ ) {
                pl.addVertex(p.contour[i].vertex[j].x, p.contour[i].vertex[j].y);
            }
            pl.close();
            res.push_back(pl);
        }
        return res;
    }
    
    inline vector<ofPolyline> getPolygonClip(opType operation, ofPolyline sub, ofPolyline clip){
        gpc_polygon a = ofToGpc(sub);
        gpc_polygon b = ofToGpc(clip);
        
        gpc_polygon res;
        
        gpc_polygon_clip((gpc_op)operation, &a, &b, &res);
        
        return gpcToOf(res);
    }
    
    inline vector<ofPolyline> getPolygonClip(opType operation, ofPath sub, ofPath clip){
        gpc_polygon a = ofToGpc(sub);
        gpc_polygon b = ofToGpc(clip);
        
        gpc_polygon res;
        
        gpc_polygon_clip((gpc_op)operation, &a, &b, &res);
        
        return gpcToOf(res);
    }
    
    
}}

namespace ofxGPC = ofx::gpc;