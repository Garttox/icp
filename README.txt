ICP 2021/2022

Authors:
- Michal Trlica (xtrlic02)
- Martin Bednář (xbedna77)

The main goal of this project is to create graphical application for 
displaying, creating, editing and saving UML class diagrams and sequence diagrams.

Application uses it's own JSON file structure to store and load diagrams.

Completion:
- Class diagram:
  fully implemented (creat, delete, editing, loading, saving)

- Sequence diagram:
  loading, editing and saving is implemented,
  interaction can be tricky in some parts, especially dragging message "boxes" can cause some inconsistencies

- Undo feature:
  undo of editing, adding is fully implemented,
  undo of removing (either from class or seq. diagram) is not implemented

- Inconsistencies: 
  implemented for loading => 
    should resolve missing classes by adding them
    should resolve missing instances by adding them
    should resolve class/sequence/instance names duplicates by renaming one of them
  inconsistencies caused by interaction are partially implemented
  calls and methods are deleted when their class is removed (intended)
  calls are deleted when instance is removed (intended)


Directory tree:
.
|-- examples  (json files for testing)
|-- res       (png icons)
|-- src 
    |-- command  (commands used to modify models and make undo)
    |-- data     (data loading/saving, model creation)
    |-- model    (model classes for manipulation of data)
    |-- view     (Qt forms and classes for painting, extending QGraphicsView or QGraphicsItem)
    |-- app.cpp  (application main file, window creation, adding scene)
    |-- app.h    
    |-- icp.pro  (Qt project file)
    |-- main.cpp (application entry point)


Sources:
- https://doc.qt.io/archives/qt-5.5/index.html
- https://doc.qt.io/qt-5/qtwidgets-graphicsview-diagramscene-example.html
