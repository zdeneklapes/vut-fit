/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file side_toolbox.cpp
 */

#include "src/gui/side-toolbox/side_toolbox.h"
#include "src/gui/canvas/canvas.h" // forward
#include "src/gui/window.h" // forward

Side_toolbox::Side_toolbox(QGraphicsScene *scene, Window *parent)
        : QTabWidget(parent),
          scene(scene),
          class_toolbox(new QToolBox()),
          sequence_toolbox(new QToolBox()),
          canvas(new Canvas(this)) {

    this->addTab(class_toolbox, "Class Diagram");
    class_toolbox->addItem(create_class_items(), "Items");

    this->addTab(sequence_toolbox, "Sequence Diagram");
    sequence_toolbox->addItem(create_sequence_items(), "Items");
    this->setCurrentIndex(0);
}

Side_toolbox::~Side_toolbox() = default;

QWidget *Side_toolbox::create_class_items() {
    // CREATING WIDGETS
    auto *item_widget = new QWidget(this);
    auto *layout = new QVBoxLayout(item_widget);
    auto *add_class_btn = new QPushButton("Add Class", item_widget);
    auto *delete_class_btn = new QPushButton("Delete Class", item_widget);
    auto *add_attribute_btn = new QPushButton("Add Attribute", item_widget);
    auto *delete_attribute_btn = new QPushButton("Delete Attribute", item_widget);
    auto *add_method_btn = new QPushButton("Add Method", item_widget);
    auto *delete_method_btn = new QPushButton("Delete Method", item_widget);
    auto *connect_classes = new QPushButton("Connect Classes", item_widget);
    auto *disconnect_classes = new QPushButton("Disconnect Classes", item_widget);
    auto *add_text_btn = new QPushButton("Add Text item", item_widget);
    auto *delete_text_btn = new QPushButton("Delete Text item", item_widget);
    p1_combo_box = new QComboBox(item_widget);
    p2_combo_box = new QComboBox(item_widget);
    auto list = QStringList();
    list.push_back("Association");
    list.push_back("Aggregation");
    list.push_back("Composition");
    list.push_back("Generalization");
    p1_combo_box->insertItems(0, list);
    p2_combo_box->insertItems(0, list);

    // CONNECT
    connect(add_class_btn, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::add_class);
    connect(delete_class_btn, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::delete_class);
    connect(add_attribute_btn, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::add_attribute);
    connect(delete_attribute_btn, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::delete_attribute);
    connect(add_method_btn, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::add_method);
    connect(delete_method_btn, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::delete_method);
    connect(connect_classes, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::connect_classes);
    connect(disconnect_classes, &QPushButton::released, canvas->get_class_diagram(),
            &Class_diagram::disconnect_classes);
    connect(p1_combo_box, &QComboBox::currentTextChanged, canvas->get_class_diagram(),
            &Class_diagram::update_connection);
    connect(p2_combo_box, &QComboBox::currentTextChanged, canvas->get_class_diagram(),
            &Class_diagram::update_connection);
    connect(add_text_btn, &QPushButton::clicked, canvas->get_class_diagram(),
            &Class_diagram::add_text_item);
    connect(delete_text_btn, &QPushButton::clicked, canvas->get_class_diagram(),
            &Class_diagram::delete_text_item);

    // LAYOUT
    item_widget->setLayout(layout);

    layout->addWidget(new QLabel("Classes"));
    layout->addWidget(add_class_btn);
    layout->addWidget(delete_class_btn);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(new QLabel("Attributes"));
    layout->addWidget(add_attribute_btn);
    layout->addWidget(delete_attribute_btn);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(new QLabel("Methods"));
    layout->addWidget(add_method_btn);
    layout->addWidget(delete_method_btn);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(new QLabel("Text"));
    layout->addWidget(add_text_btn);
    layout->addWidget(delete_text_btn);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(new QLabel("Relation"));
    layout->addWidget(connect_classes);
    layout->addWidget(disconnect_classes);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(new QLabel("Choose relation types:"));
    layout->addWidget(p1_combo_box);
    layout->addWidget(p2_combo_box);

//    layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    layout->setAlignment(Qt::AlignTop);
    return item_widget;
}

QWidget *Side_toolbox::create_sequence_items() {
    auto btn_delete = new QPushButton("Delete");
    connect(btn_delete, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::delete_items);
    auto btn_new_actor = new QPushButton("New Actor");
    connect(btn_new_actor, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::create_actor);
    auto btn_new_object = new QPushButton("New Object");
    connect(btn_new_object, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::create_object);
    auto resizer = new Resizer(canvas->get_scene());
    auto btn_new_box = new QPushButton("New Box");
    connect(btn_new_box, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::create_box);

    QString entity_text_first;
    auto text_first_input = new QLabel("Entity From");
    auto input_first_entity = new Input_entity(1);
    auto text_second_input = new QLabel("Entity To");
    auto input_second_entity = new Input_entity(2);
    auto text_diagram_name = new QLabel("Working On Diagram:");
    auto input_diagram_name = new Input_entity(3);
    input_diagram_name->input->setText("Default Name");
    (canvas->get_sequence_diagram())->input_diagram_name = input_diagram_name;

    auto btn_set_diagram = new QPushButton("Set Diagram By Entity");
    connect(btn_set_diagram, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::set_diagram);

    auto btn_new_message_sync = new QPushButton("New Synchronous Message ");
    connect(btn_new_message_sync, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::create_message_sync);
    auto btn_new_message_async = new QPushButton("New Asynchronous Message ");
    connect(btn_new_message_async, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::create_message_async);
    auto btn_new_message_create = new QPushButton("New Create Message");
    connect(btn_new_message_create, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::create_message_create);
    auto btn_new_message_async_return = new QPushButton(
            "New Asynchronous\n Return / Reply Message");
    connect(btn_new_message_async_return, &QPushButton::released, canvas->get_sequence_diagram(),
            &Sequence_diagram::create_message_async_return);

    auto text_resizer = new QLabel("Resizer");

    auto itemWidget = new QWidget();
    auto *layout = new QVBoxLayout();

    itemWidget->setLayout(layout);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(text_diagram_name);
    layout->addWidget(input_diagram_name->input);
    layout->addWidget(btn_set_diagram);

    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(btn_new_actor);
    layout->addWidget(btn_new_object);
    layout->addWidget(btn_new_box);
    layout->addWidget(btn_delete);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(text_first_input);
    layout->addWidget(input_first_entity->input);
    layout->addWidget(text_second_input);
    layout->addWidget(input_second_entity->input);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(btn_new_message_sync);
    layout->addWidget(btn_new_message_async);
    layout->addWidget(btn_new_message_create);
    layout->addWidget(btn_new_message_async_return);
    layout->addSpacerItem(new QSpacerItem(100, 20));

    layout->addWidget(text_resizer);
    layout->addWidget(resizer->slider);
    layout->setAlignment(Qt::AlignTop);
//    layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    return itemWidget;
}


QToolBox *Side_toolbox::get_class_toolbox() { return this->class_toolbox; }

QComboBox *Side_toolbox::get_relation_type(int type_number) {
    if (type_number == 1)
        return (QComboBox *) get_class_toolbox()->currentWidget()->layout()->itemAt(
                get_class_toolbox()->currentWidget()->layout()->count() - 2)->widget();
    else
        return (QComboBox *) get_class_toolbox()->currentWidget()->layout()->itemAt(
                get_class_toolbox()->currentWidget()->layout()->count() - 1)->widget();
}

QGraphicsScene *Side_toolbox::get_scene() { return canvas->get_scene(); }

Canvas *Side_toolbox::get_canvas() { return canvas; }
