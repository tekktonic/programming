package in.tekk.apphack8

import android.app.Activity
import android.location
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.graphics.drawable.Animatable

import scala.collection.mutable.HashMap


object MessageType extends Enumeration {
  type MessageType = Value

  val Feed, Water = Value
}

class Event[A](typ: MessageType, value: A){
  def getType = {typ}
  def getValue[A] = {value}
}


trait Component {
  def update()
  def receive(e: Event)
}

class HungerComponent(owner: Entity, hungerScale: Int = 180) extends Component {
  var hunger = 60
  var counter = hungerScale
  var string = "alive!"
  def update() = {
    counter--

    if (counter <= 0) {
      hunger--;
    }

    if (dead()) {
      string = "dead :c"
    }
  }

  def receive
  def dead() = { hunger <= 0}

  override def toString() {string}
}

class Entity() {
  var components = new HashMap[String, Component]()
  def init() = {
    components += (("foo", new Component))
  }
  def printMe() = {
    components.get("foo").getOrElse(new Component).toString()
  }
}

class MainActivity extends AppCompatActivity {
  // allows accessing `.value` on TR.resource.constants
  implicit val context = this

  override def onCreate(savedInstanceState: Bundle): Unit = {
    
    super.onCreate(savedInstanceState)
    // type ascription is required due to SCL-10491
    val vh: TypedViewHolder.main = TypedViewHolder.setContentView(this, TR.layout.main)
    val c: Entity = new Entity
    c.init()
    vh.text.setText(c.printMe())
            
  }
}
