import matplotlib.pyplot as plt   

if __name__ == "__main__":
    x = [10000,40000,90000,160000,250000,360000,490000,640000,810000,1000000]
    y = [8,70,241,563,1080,1889,2958,4503,6563,8908]
    plt.plot(x, y)
    plt.xlabel('Кол-во элементов')
    plt.ylabel('Время выполнения,мс')
    plt.title('Зависимость времени от кол-ва элементов')
    plt.show()