//
//  Shader.h
//  DetuPanoPlayer
//
//  Created by zhangjing on 2017/5/22.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#define PANO_GLES_STRINGIZE(x)   #x
#if defined(MAC_QT)
#define PANO_FRAGMENT_PRECISION 
#elif defined(__APPLE__)
#define PANO_FRAGMENT_PRECISION "precision mediump float;"
#elif defined(WIN32)
#define PANO_FRAGMENT_PRECISION ""
#else
#define PANO_FRAGMENT_PRECISION "precision mediump float;"
#endif
#ifdef __cplusplus
extern "C" {
#endif
    //CUBE SHADER
    static const char CUBE_VERTEXT_SHADER[] =
    "uniform mat4 u_MVPMatrix;\n" \
    "attribute vec4 a_Position;\n" \
    "attribute vec2 a_TexCoordinate;\n" \
    "varying vec2 v_TexCoordinate;\n" \
    "void main()\n" \
    "{\n" \
    "    v_TexCoordinate = a_TexCoordinate;\n" \
    "    gl_Position = u_MVPMatrix * a_Position;\n" \
    "}\n";
    
    static const char CUBE_FRAG_SHADER[] =
    "uniform sampler2D u_Texture;\n" \
    "varying vec2 v_TexCoordinate;\n" \
    "void main()\n"\
    "{\n" \
    "gl_FragColor = texture2D(u_Texture, v_TexCoordinate);\n" \
    "}\n";
    
    //STANDARDSPHERE SHADER
    static const char STANDARD_VERTEXT_SHADER[] =
    PANO_GLES_STRINGIZE(
                        uniform
                        mat4 u_MVPMatrix;
                        attribute
                        vec4 a_Position;
                        attribute
                        vec2 a_TexCoordinate;
                        varying
                        vec2 v_TexCoordinate;
                        void main() {
                            v_TexCoordinate = a_TexCoordinate;
                            gl_Position = u_MVPMatrix * a_Position;
                        }
                        );
    
    static const char STANDARD_FRAG_SHADER[] =
    PANO_GLES_STRINGIZE(
                        uniform
                        sampler2D u_Texture;
                        varying
                        vec2 v_TexCoordinate;
                        uniform float alpha;
                        uniform int isbgra;
                        
                        void main() {
                            if (isbgra == 1) {
                                vec3 col = texture2D(u_Texture, v_TexCoordinate).rgb;
                                gl_FragColor = vec4(col.b, col.g, col.r, alpha);
                            } else {
                                gl_FragColor = vec4(texture2D(u_Texture, v_TexCoordinate).rgb, alpha);
                            }
                        }
                        );
    
    //STANDARDSPHERE SHADER
    static const char SPACE3D_VERTEXT_SHADER[] =
    PANO_GLES_STRINGIZE(
                        uniform mat4 u_MVPMatrix;
                        attribute vec4 a_Position;
                        attribute vec2 a_TexCoordinate;
                        attribute vec3 a_Normal;

                        varying vec2 v_TexCoordinate;
                        void main() {
                            v_TexCoordinate = a_TexCoordinate;
                            gl_Position = u_MVPMatrix * a_Position;
                        }
                        );
    
    static const char SPACE3D_FRAG_SHADER[] =
    PANO_GLES_STRINGIZE(
                        uniform  sampler2D u_Texture;
                        varying vec2 v_TexCoordinate;
                        void main() {
                            gl_FragColor = texture2D(u_Texture, v_TexCoordinate);
                        }
                        );
    
    //SphereEye SHADER
    static const char SphereEye_VERTEXT_SHADER[] =
    PANO_GLES_STRINGIZE(
                        uniform
                        mat4 u_MVPMatrix;
                        attribute
                        vec4 a_Position;
                        attribute
                        vec2 a_TexCoordinate;
                        varying
                        vec2 v_TexCoordinate;
                        varying float v_pos_y;
                        
                        void main() {
                            v_TexCoordinate = a_TexCoordinate;
                            gl_Position = u_MVPMatrix * a_Position;
                            v_pos_y = a_Position.y;
                            
                        }
                        );
    
    static const char SphereEye_FRAG_SHADER[] =
    PANO_GLES_STRINGIZE(
                        uniform
                        sampler2D u_Texture;
                        varying
                        vec2 v_TexCoordinate;
                        varying float v_pos_y;
                        uniform float ylimt;
                        uniform int modetype;
                        void main() {
                            vec4 Tcolor = texture2D(u_Texture, v_TexCoordinate);
                            if (modetype == 2) {
                                gl_FragColor = Tcolor;
                                
                            } else if (modetype == 1) {
                                if (v_pos_y > ylimt) {
                                    gl_FragColor = Tcolor;
                                } else {
                                    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
                                }
                            }
                        }
                        );
    
    //Sphere2Eye SHADER
    static const char Sphere2Eye_VERTEXT_SHADER[] =
    PANO_GLES_STRINGIZE(
                        attribute
                        vec4 a_Position;
                        attribute
                        vec2 a_TexCoordinateA;
                        attribute
                        vec2 a_TexCoordinateB;
                        uniform
                        mat4 u_MVPMatrix;
                        varying
                        vec2 v_TexCoordinateA;
                        varying
                        vec2 v_TexCoordinateB;
                        varying float v_pos_x;
                        varying float v_pos_y;
                        varying float v_pos_z;
                        void main() {
                            gl_Position = u_MVPMatrix * a_Position;
                            v_TexCoordinateA = a_TexCoordinateA;
                            v_TexCoordinateB = a_TexCoordinateB;
                            v_pos_x = a_Position.x;
                            v_pos_y = a_Position.y;
                            v_pos_z = a_Position.z;
                        }
                        );
    
    static const char Sphere2Eye_FRAG_SHADER[] =
    PANO_GLES_STRINGIZE(
                        varying float v_pos_x;
                        varying float v_pos_y;
                        varying float v_pos_z;
                        varying
                        vec2 v_TexCoordinateA;
                        varying
                        vec2 v_TexCoordinateB;
                        uniform
                        sampler2D u_Texture;
                        uniform int modetype;
                        uniform float gamma;
                        uniform float yaw0;
                        uniform float yaw1;
                        uniform float x_rate;
                        uniform float y_rate;
                        float M_PI = 3.14159265358979;
                        uniform float v_maskdegree;
                        vec4 getColor(vec4 colA, vec4 colB, float degree, float maskdegree);
                        
                        void main() {
                            vec4 colA;
                            vec4 colB;
                            colA = texture2D(u_Texture, v_TexCoordinateA);
                            colB = texture2D(u_Texture, v_TexCoordinateB);
                            float alpha = 0.0;
                            float v_masksize = v_maskdegree / 180.0;
                            if (modetype == 1) {
                                
                                float point;
                                point = v_pos_x;
                                float masksize = v_masksize;
                                float Midsize = 0.0;
                                float y_dre = (v_pos_y + 1.0) * 90.0;
                                if (y_dre < 5.0) {
                                    
                                    masksize = y_dre * v_maskdegree / 5.0 / 180.0;
                                }
                                
                                if (point < Midsize - masksize) {
                                    alpha = 0.0;
                                } else if (point > Midsize + masksize) {
                                    alpha = 1.0;
                                } else {
                                    float index = point - (Midsize - masksize);
                                    float al = index * 1.0 / (masksize * 2.0);
                                    alpha = al;
                                }
                                gl_FragColor = colA * alpha + colB * (1.0 - alpha);
                            } else if (modetype == 2) {
                                float degree = v_pos_x * 180.0 + 180.0;
                                float maskdegree = v_maskdegree;
                                
                                float R = 90.0;
                                float R1 = v_maskdegree / 2.0;
                                float pos_y_d = (v_pos_y + 1.0) * 90.0;
                                
                                
                                if (pos_y_d > 90.0) {
                                    
                                    if (pos_y_d < R1 || pos_y_d > 180.0 - R1) {
                                        
                                        maskdegree = 90.0;
                                    } else {
                                        pos_y_d = 90.0 - pos_y_d;
                                        //calc blend width
                                        maskdegree = (sqrt(R * R - (pos_y_d) * (pos_y_d)) -
                                                      sqrt((R - R1) * (R - R1) - (pos_y_d) * (pos_y_d))) /
                                        sqrt(R * R - (pos_y_d) * (pos_y_d)) * 90.0;
                                    }
                                    
                                } else {
                                    pos_y_d = pos_y_d - 90.0;
                                    
                                    maskdegree = maskdegree / 2.0;
                                    
                                }
                                maskdegree = maskdegree * x_rate;
                                vec4 t_rgb = getColor(colA, colB, degree, maskdegree);
                                vec3 v_rgb = pow(vec3(t_rgb.r, t_rgb.g, t_rgb.b), vec3(1.0 / gamma));
                                gl_FragColor = vec4(v_rgb, 1.0);
                            } else if (modetype == 3) {
                                gl_FragColor = colA;
                            }
                            
                            
                        }
                        
                        vec4 getColor(vec4 colA, vec4 colB, float degree, float maskdegree) {
                            vec4 col;
                            float yaw00 = 180.0 - (x_rate * 180.0) / 2.0;
                            float yaw11 = 180.0 + (x_rate * 180.0) / 2.0;
                            if (yaw00 < yaw11) {
                                if (yaw11 + maskdegree > 360.0) {
                                    if (degree < maskdegree * 2.0) {
                                        degree += 360.0;
                                    }
                                }
                                if (yaw00 - maskdegree < 0.0) {
                                    if (degree > (360.0 - 2.0 * maskdegree)) {
                                        degree -= 360.0;
                                    }
                                }
                                if (degree > (yaw00 + maskdegree) && degree <= (yaw11 - maskdegree)) {
                                    col = colB;
                                } else if (degree > (yaw11 - maskdegree) && degree <= (yaw11 + maskdegree)) {
                                    float index = degree - (yaw11 - maskdegree);
                                    float al = index * 1.0 / (maskdegree * 2.0);
                                    
                                    col = colA * al + colB * (1.0 - al);
                                } else if (degree > (yaw00 - maskdegree) && degree <= (yaw00 + maskdegree)) {
                                    float index = degree - (yaw00 - maskdegree);
                                    float al = index * 1.0 / (maskdegree * 2.0);
                                    col = colB * al + colA * (1.0 - al);
                                } else {
                                    col = colA;
                                }
                                
                            }
                            return col;
                        }
                        
                        );
    
    
    
    
    // Sphere4Eye SHADER
    
    static const char Sphere4Eye_VERTEXT_SHADER[] =
    PANO_GLES_STRINGIZE(
                        uniform
                        mat4 u_MVPMatrix;
                        attribute
                        vec4 a_Position;
                        attribute
                        vec2 a_TexCoordinate0;
                        attribute
                        vec2 a_TexCoordinate1;
                        attribute
                        vec2 a_TexCoordinate2;
                        attribute
                        vec2 a_TexCoordinate3;
                        
                        attribute
                        vec2 a_weightCoordinate;
                        
                        varying
                        vec2 v_TexCoordinate0;
                        varying
                        vec2 v_TexCoordinate1;
                        varying
                        vec2 v_TexCoordinate2;
                        varying
                        vec2 v_TexCoordinate3;
                        
                        varying
                        vec2 v_weightCoordinate;
                        
                        
                        void main() {
                            gl_Position = u_MVPMatrix * a_Position;
                            v_TexCoordinate0 = a_TexCoordinate0;
                            v_TexCoordinate1 = a_TexCoordinate1;
                            v_TexCoordinate2 = a_TexCoordinate2;
                            v_TexCoordinate3 = a_TexCoordinate3;
                            
                            v_weightCoordinate = a_weightCoordinate;
                        }
                        );
    
    static const char Sphere4Eye_FRAG_SHADER[] =
    PANO_GLES_STRINGIZE(
                        varying
                        vec2 v_TexCoordinate0;
                        varying
                        vec2 v_TexCoordinate1;
                        varying
                        vec2 v_TexCoordinate2;
                        varying
                        vec2 v_TexCoordinate3;
                        
                        varying
                        vec2 v_weightCoordinate;
                        
                        uniform
                        sampler2D u_Texture;
                        uniform
                        sampler2D weight_Texture0;
                        uniform
                        sampler2D weight_Texture1;
                        uniform
                        sampler2D weight_Texture2;
                        uniform
                        sampler2D weight_Texture3;
                        
                        uniform int viewtype;
                        vec4 BlendColor(vec4 mcol[4], float weightcol[4]) {
                            vec3 col = vec3(0.0, 0.0, 0.0);
                            float weight_total = 0.0;
                            for (int i = 0; i < 4; i++) {
                                col += mcol[i].rgb * weightcol[i];
                                weight_total += weightcol[i];
                            }
                            col /= weight_total;
                            return vec4(col, 1.0);
                        }
                        void main() {
                            vec4 mcol[4];
                            float weightcol[4];
                            mcol[0] = texture2D(u_Texture, v_TexCoordinate0);
                            mcol[1] = texture2D(u_Texture, v_TexCoordinate1);
                            mcol[2] = texture2D(u_Texture, v_TexCoordinate2);
                            mcol[3] = texture2D(u_Texture, v_TexCoordinate3);
                            
                            weightcol[0] = texture2D(weight_Texture0, v_weightCoordinate).r;
                            weightcol[1] = texture2D(weight_Texture1, v_weightCoordinate).r;
                            weightcol[2] = texture2D(weight_Texture2, v_weightCoordinate).r;
                            weightcol[3] = texture2D(weight_Texture3, v_weightCoordinate).r;
                            if (viewtype == 1) {//全景模式
                                gl_FragColor = BlendColor(mcol, weightcol);
                            } else if (viewtype == 2) {
                                gl_FragColor = mcol[0];
                            }
                            
                        });
    
    //real 3d SHADER
    static const char Real3D_VERTEXT_SHADER[] =
    PANO_GLES_STRINGIZE(
                        attribute vec4 a_Position;
                        attribute vec2 a_TexCoordinate;
                        
                        uniform mat4 u_MVPMatrix;
                        varying vec2 v_TexCoordinate;
                        
                        void main() {
                            gl_Position = u_MVPMatrix * a_Position;
                            v_TexCoordinate = a_TexCoordinate;
                        }
                        );
    
    static const char Real3D_FRAG_SHADER[] =
    PANO_GLES_STRINGIZE(
                        varying vec2 v_TexCoordinate;
                        uniform sampler2D u_Texture;
                        
                        void main() {
                            gl_FragColor = texture2D(u_Texture, v_TexCoordinate);
                        }
                        );
    
    
#ifdef __cplusplus
}
#endif
#endif /* Shader_h */
