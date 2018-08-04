import pickle


def read_pickle(pickle_path):
    with open(pickle_path, 'rb') as f:
        return pickle.load(f)

