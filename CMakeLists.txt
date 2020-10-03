cmake_minimum_required(VERSION 3.17)
project(Tarea1_Datos2)

set(CMAKE_CXX_STANDARD 14)

add_executable( Tarea1_Datos2
        main.cpp
        ServerSocket.h
        LinkedList.h
        Graph.h

        GUI/ClientSocket.h
        GUI/addedge.cpp
        GUI/addedge.h
        GUI/addedge.ui
        GUI/addvertex.cpp
        GUI/addvertex.h
        GUI/addedge.ui
        GUI/deleteedge.cpp
        GUI/deleteedge.h
        GUI/deleteedge.ui
        GUI/deletevertex.cpp
        GUI/deletevertex.h
        GUI/deletevertex.ui
        GUI/GUI.pro
        GUI/GUI.pro.user
        GUI/GUI_en_US.ts
        GUI/main.cpp
        GUI/mainwindow.cpp
        GUI/mainwindow.h
        GUI/mainwindow.ui
)