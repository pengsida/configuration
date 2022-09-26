# https://github.com/intel-isl/Open3D/issues/387
import open3d as o3d

# asssume we have a point cloud pc
vis = o3d.visualization.Visualizer()
vis.create_window()
ctr = vis.get_view_control()
vis.add_geometry(pc)

# set viewpoints
o3d_param = np.load('o3d_param.npy', allow_pickle=True).item()
param = o3d.camera.PinholeCameraParameters()
param.extrinsic = o3d_param['extri']
param.intrinsic.set_intrinsics(*o3d_param['intri'])
ctr.convert_from_pinhole_camera_parameters(param)

# manually set viewpoints
# vis.run()
# param = ctr.convert_to_pinhole_camera_parameters()
# extrinsic = param.extrinsic
# intrinsic = param.intrinsic
# width, height = intrinsic.width, intrinsic.height
# fx, fy = intrinsic.get_focal_length()
# cx, cy = intrinsic.get_principal_point()
# np.save('o3d_param.npy', {'extri': extrinsic, 'intri': [width, height, fx, fy, cx, cy]})

vis.update_geometry(pc)
vis.poll_events()
vis.update_renderer()
vis.capture_screen_image('tmp.jpg')
vis.destroy_window()
