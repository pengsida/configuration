import scipy.io as sio
import numpy as np


class PascalObject(object):
    def __init__(self, pascal_object):
        self.pascal_object = pascal_object

    @property
    def object_class(self):
        return self.pascal_object['class'][0]

    @property
    def bbox(self):
        return self.pascal_object['bbox'][0]

    @property
    def kps_name(self):
        anchors = self.pascal_object['anchors']
        fields = anchors.dtype.fields
        return list(fields.keys())

    @property
    def kps(self):
        anchors = self.pascal_object['anchors']
        fields = anchors.dtype.fields
        kps = np.zeros(shape=[len(fields), 3])
        for i, field in enumerate(fields):
            anchor = anchors[field][0, 0]
            kps[i, 0] = anchor['status'][0, 0][0, 0]
            if kps[i, 0] == 2:
                continue
            kps[i, 1:] = anchor['location'][0, 0][0]
        return kps

    @property
    def viewpoint(self):
        viewpoint = self.pascal_object['viewpoint']
        fields = viewpoint.dtype.fields
        viewpoint_dict = {}
        for field in fields:
            value = viewpoint[field][0, 0][0, 0]
            viewpoint_dict[field] = value
        return viewpoint_dict

    @property
    def cad_index(self):
        return self.pascal_object['cad_index'][0, 0]

    @property
    def sub_type(self):
        return self.pascal_object['subtype'][0]

    @property
    def sub_label(self):
        return self.pascal_object['sub_label'][0, 0]

    @property
    def sub_index(self):
        return self.pascal_object['sub_index'][0, 0]

    @property
    def truncated(self):
        return self.pascal_object['truncated'][0, 0]

    @property
    def difficult(self):
        return self.pascal_object['difficult'][0, 0]



class PascalAnnotationParser(object):
    def __init__(self, annot_path):
        self.record = sio.loadmat(annot_path)['record']

    @property
    def filename(self):
        data = self.record['filename'][0, 0]
        return data[0]

    @property
    def img_size(self):
        # return: h, w, c
        data = self.record['size'][0, 0]
        width = data['width'][0, 0][0, 0]
        height = data['height'][0, 0][0, 0]
        channel = data['depth'][0, 0][0, 0]
        return height, width, channel

    @property
    def database(self):
        data = self.record['database'][0, 0]
        return data[0]

    @property
    def objects(self):
        object_list = []
        objects = self.record['objects'][0, 0]
        n = objects.shape[1]
        for i in range(n):
            object_list.append(PascalObject(objects[0, i]))
        return object_list


if __name__ == '__main__':
    parser = PascalAnnotationParser('/mnt/data/home/pengsida/Datasets/PASCAL3D+_release1.1/Annotations/car_imagenet/n02814533_2054.mat')
    print(parser.database)
    print(parser.filename)
    print(parser.img_size)

    pascal_objects = parser.objects
    print(pascal_objects[0].kps)
    print(pascal_objects[0].bbox)
    print(pascal_objects[0].cad_index)
    print(pascal_objects[0].difficult)
    print(pascal_objects[0].object_class)
    print(pascal_objects[0].sub_index)
    print(pascal_objects[0].sub_label)
    print(pascal_objects[0].sub_type)
    print(pascal_objects[0].truncated)
    print(pascal_objects[0].viewpoint)

