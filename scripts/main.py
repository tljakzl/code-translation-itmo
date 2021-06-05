import matplotlib.pyplot as plt
import numpy as np

timeLabel = 'Время (милисекунды)'
coutLabel = 'Количество элементов шт.'

tm32 = np.genfromtxt('testMemory_32.csv', delimiter=';')
tF8 = np.genfromtxt('testFind_8.csv', delimiter=';')
tF32 = np.genfromtxt('testFind_32.csv', delimiter=';')
tI32 = np.genfromtxt('testInsert_32.csv', delimiter=';')
tI8 = np.genfromtxt('testInsert_8.csv', delimiter=';')


fig, ax = plt.subplots()
ax.plot(tm32[:,0], tm32[:,1])
ax.plot(tm32[:,0], tm32[:,2])
ax.plot(tm32[:,0], tm32[:,3])
ax.set(xlabel=coutLabel, ylabel='Память (Байт)',
       title='Занимаемая память, длина идентификатора 32 символоа \n')
ax.legend(['Хеш-таблица', 'Дерево поиска','Неупорядоченный массив'])
ax.grid()
fig.savefig("tm32.png")
plt.show()




fig, ax = plt.subplots()
ax.plot(tI32[:,0], tI32[:,1])
ax.plot(tI8[:,0], tI8[:,1])

ax.set(xlabel=coutLabel, ylabel=timeLabel,
       title='Вставка элементов в хеш таблицу')
ax.legend(['Длина идентификатора 8', 'Длина идентификатора 32'])
ax.grid()
fig.savefig("tI32.png")
plt.show()




fig, ax = plt.subplots()
ax.plot(tI8[:,0], tI8[:,2])
ax.plot(tI32[:,0], tI32[:,2])
ax.plot(tI8[:,0], tI8[:,3])
ax.plot(tI32[:,0], tI32[:,3])
ax.set(xlabel=coutLabel, ylabel=timeLabel,
       title='Вставка элементов')
ax.legend(['Дерево поиска (длина 8)', 'Дерево поиска (длина 32)','Неупорядоченный массив (длина 8)','Неупорядоченный массив (длина 32)'])
ax.grid()
fig.savefig("tI8.png")
plt.show()




fig, ax = plt.subplots()
ax.plot(tF8[:,0], tF8[:,1])
ax.plot(tF32[:,0], tF32[:,1])
ax.set(xlabel=coutLabel, ylabel=timeLabel,
       title='Поиск элементов хеш-таблица')
ax.legend(['Длина идентификатора 8', 'Длина идентификатора 32'])
ax.grid()
fig.savefig("tF8.png")
plt.show()





fig, ax = plt.subplots()
ax.plot(tF32[:,0], tF32[:,2])
ax.plot(tF8[:,0], tF8[:,2])
ax.set(xlabel=coutLabel, ylabel=timeLabel,
       title='Поиск элементов АВЛ-дерево')
ax.legend(['Длина идентификатора 8', 'Длина идентификатора 32'])
ax.grid()
fig.savefig("FT8-32.png")
plt.show()





fig, ax = plt.subplots()
ax.plot(tF8[:,0], tF8[:,3])
ax.plot(tF32[:,0], tF32[:,3])
ax.set(xlabel=coutLabel, ylabel=timeLabel,
       title='Поиск элементов неупорядоченный массив')
ax.legend(['Длина идентификатора 8', 'Длина идентификатора 32'])
ax.grid()

fig.savefig("tF32.png")
plt.show()

