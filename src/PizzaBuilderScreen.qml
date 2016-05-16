import QtQuick 2.5

Rectangle {
    color:"blue"
    Rectangle{
        id: banner
        anchors.left:parent.left
        anchors.top:parent.top
        color:"red"
        width:parent.width/5
        height:parent.height/16
        border.width:2

        Text{
            anchors.fill: parent
            anchors.leftMargin: 4
            text:"Pizza Builder"
            font.pixelSize: 26
            font.bold: true
            color:"white"
            verticalAlignment: Text.AlignVCenter
        }
    }
    // Connect PizzaBuilder C++ class to livePizzaImage source reset
    Connections {
        target: PizzaBuilder
        onUpdateLivePizza: {
            livePizzaImage.source = ""
            //livePizzaImage.opacity = 0.3
            livePizzaImage.source = "image://live/pizza"
        }
    }

    Image{
        id:livePizzaImage
        source: ""
        asynchronous: true
        cache:false
        anchors.verticalCenter: parent.verticalCenter
        anchors.right:availableContainer.left
        anchors.rightMargin: 20
        width:523
        height:528
    }

    ListContainer{
        id: availableContainer
        anchors.right: parent.right
        anchors.top: parent.top
        height:parent.height/3
        width:parent.width/4
        border.width: 2
        radius:4
        titleText:"Available Toppings"
        Component.onCompleted: {
            listData.append({"name":"Anchovies"})
            listData.append({"name":"Pepperoni"})
            listData.append({"name":"Pineapple"})
            listData.append({"name":"Tomatoes"})
            listData.append({"name":"Nuka-roni"})
        }
        onClickedItem: {
            PizzaBuilder.chooseTopping(listData.get(index).name)
            chosenContainer.listData.append({"name" : listData.get(index).name})
            listData.remove(index)
        }
    }

    ListContainer{
        id: chosenContainer
        anchors.right: parent.right
        anchors.top: availableContainer.bottom
        anchors.topMargin:4
        height:parent.height/3
        width:parent.width/4
        border.width: 2
        radius:4
        titleText:"Chosen Toppings"
        onClickedItem: {
            PizzaBuilder.removeTopping(listData.get(index).name)
            availableContainer.listData.append({"name" : listData.get(index).name})
            listData.remove(index)
        }

        Component.onCompleted: {

        }
    }

    Component.onCompleted: {
        livePizzaImage.source = "image://live/pizza"; // Request the pixmap on load
    }

}
