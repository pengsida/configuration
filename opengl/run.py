import opengl_utils
import inout
import matplotlib.pyplot as plt
import numpy as np

obj_path = 'cat.ply'
model = inout.load_ply(obj_path)
model['pts'] = model['pts'] * 1000.
im_size = (640, 480)
opengl = opengl_utils.NormalRender(model, im_size)

K = np.array([[572.4114, 0., 325.2611],
              [0., 573.57043, 242.04899],
              [0., 0., 1.]])
pose = np.array([[ 0.0950661,  0.983309 , -0.155129,  0.0717302 ],
                 [ 0.741596 , -0.173913 , -0.647911, -0.14907229],
                 [-0.664076 , -0.0534489, -0.745752,  1.0606388 ]], dtype=np.float32)
depth = opengl.render(im_size, 100, 10000, K, pose[:, :3], pose[:, 3:] * 1000)

plt.imshow(depth)
plt.show()
