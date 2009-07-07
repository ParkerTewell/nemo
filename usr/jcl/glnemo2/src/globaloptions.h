// ============================================================================
// Copyright Jean-Charles LAMBERT - 2007-2008                                  
// e-mail:   Jean-Charles.Lambert@oamp.fr                                      
// address:  Dynamique des galaxies                                            
//           Laboratoire d'Astrophysique de Marseille                          
//           P�le de l'Etoile, site de Ch�teau-Gombert                         
//           38, rue Fr�d�ric Joliot-Curie                                     
//           13388 Marseille cedex 13 France                                   
//           CNRS U.M.R 6110                                                   
// ============================================================================
// See the complete license in LICENSE and/or "http://www.cecill.info".        
// ============================================================================
/**
	@author Jean-Charles Lambert <Jean-Charles.Lambert@oamp.fr>
 */
#ifndef GLNEMOGLOBALOPTIONS_H
#define GLNEMOGLOBALOPTIONS_H

#include <QColor>
#include <vector>
namespace glnemo {


class GlobalOptions{
public:
    GlobalOptions();
    ~GlobalOptions();
    const GlobalOptions& operator=(const GlobalOptions& m);
    // from play option TAB
    bool auto_play_screenshot;
    bool auto_gl_screenshot;
    bool auto_com;
    int play_fps;
    int frame_index;
    int frame_height;
    int frame_width;
    QString base_frame_name;
    QString base_frame_ext;
    int auto_screen_size_index;
    // from OpenGL TAB
    bool show_part;
    bool show_points;
    bool show_vel;
    float psize;
    float vel_vector_size;
    int particles_alpha;
    bool blending;
    bool dbuffer;
    bool perspective;
    bool orthographic;
    bool use_shaders;
    int render_mode;
    bool init_glsl;
    // from camera tab
    bool cam_mode;
    bool cam_display_ctrl;
    bool cam_display_spline;
    bool cam_play;
    // from Scene Orientation TAB
    float zoom,zoomo;
    float xrot,yrot,zrot;
    float xtrans,ytrans,ztrans;
    // from Grids TAB
    bool show_grid;
    float mesh_length;
    int nb_meshs;
    bool xy_grid, yz_grid, xz_grid, show_cube;
    QColor col_x_grid, col_y_grid, col_z_grid, col_cube;
    // from HUD TAB
    bool show_osd;
    bool osd_title, osd_time, osd_zoom, osd_rot,
    osd_trans, osd_data_type, osd_nbody, osd_projection;
    QColor background_color, osd_color;
    // from experimental TAB
    bool show_poly;
    float texture_size;
    int texture_alpha_color;
    bool octree_enable;
    bool octree_display;
    int octree_level;
    // network;
    int port;
    // const
    static float MAX_PARTICLES_SIZE;
    static float MAX_TEXTURE_SIZE;
    static float MAX_VEL_VECTOR_SIZE;
    // velocity
    bool vel_req;
    // method
    void copyTransform(const GlobalOptions &m);
    // frame
    bool new_frame;
    // memory
    bool duplicate_mem;
    // density
    bool dens_local;
    float dens_max_glob;
    float dens_min_glob;
    static bool rho_exist;
    // colormap
    int colormap;
    bool reverse_cmap; // reverse colormap
    std::vector <float> *R,*G,*B;
    float powercolor, poweralpha;
    bool constant_cmap;
    // z sorting
    bool zsort;
};

}

#endif
