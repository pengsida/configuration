import matplotlib.pyplot as plt


def visualize_bbox_np(img, boxes):
    """
    img: [h, w, 3]
    boxes: [n, 4], [[x, y, x_max, y_max]]
    """
    import matplotlib.patches as patches

    _, ax = plt.subplots(1)
    ax.imshow(img)
    n = len(boxes)
    for ni in range(n):
        x, y, x_max, y_max = boxes[ni]
        ax.add_patch(patches.Polygon(xy=[[x, y], [x, y_max], [x_max, y_max], [x_max, y]], fill=False, linewidth=1, edgecolor='r'))
    plt.show()


def visualize_pascal_kps_np(img, kps):
    """
    img: [h, w, 3]
    kps: [n, 3]
    """
    plt.figure(figsize=(10, 8))
    plt.imshow(img)
    kps = kps[kps[:, 0] == 1][:, 1:]
    plt.scatter(kps[:, 0], kps[:, 1], c='red', s=10)
    plt.show()

