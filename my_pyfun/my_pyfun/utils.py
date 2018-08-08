import pickle
import matplotlib.pyplot as plt


def read_pickle(pickle_path):
    with open(pickle_path, 'rb') as f:
        return pickle.load(f)


def save_pickle(data, pickle_path):
    with open(pickle_path, 'wb') as f:
        return pickle.dump(data, f)


def show_img(img):
    plt.imshow(img)
    plt.show()

