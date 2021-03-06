// Generated by gencpp from file serial_mcu/robocupController.msg
// DO NOT EDIT!


#ifndef SERIAL_MCU_MESSAGE_ROBOCUPCONTROLLER_H
#define SERIAL_MCU_MESSAGE_ROBOCUPCONTROLLER_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace serial_mcu
{
template <class ContainerAllocator>
struct robocupController_
{
  typedef robocupController_<ContainerAllocator> Type;

  robocupController_()
    : firstHalf(0)
    , kickoffTeam(0)
    , state(0)
    , penalty(0)  {
    }
  robocupController_(const ContainerAllocator& _alloc)
    : firstHalf(0)
    , kickoffTeam(0)
    , state(0)
    , penalty(0)  {
  (void)_alloc;
    }



   typedef int64_t _firstHalf_type;
  _firstHalf_type firstHalf;

   typedef int64_t _kickoffTeam_type;
  _kickoffTeam_type kickoffTeam;

   typedef int64_t _state_type;
  _state_type state;

   typedef int64_t _penalty_type;
  _penalty_type penalty;





  typedef boost::shared_ptr< ::serial_mcu::robocupController_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::serial_mcu::robocupController_<ContainerAllocator> const> ConstPtr;

}; // struct robocupController_

typedef ::serial_mcu::robocupController_<std::allocator<void> > robocupController;

typedef boost::shared_ptr< ::serial_mcu::robocupController > robocupControllerPtr;
typedef boost::shared_ptr< ::serial_mcu::robocupController const> robocupControllerConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::serial_mcu::robocupController_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::serial_mcu::robocupController_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace serial_mcu

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'serial_mcu': ['/home/robit/catkin_ws/src/serial_mcu/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::serial_mcu::robocupController_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::serial_mcu::robocupController_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::serial_mcu::robocupController_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::serial_mcu::robocupController_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::serial_mcu::robocupController_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::serial_mcu::robocupController_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::serial_mcu::robocupController_<ContainerAllocator> >
{
  static const char* value()
  {
    return "363960c0c6948d0cf00f4ffede979e51";
  }

  static const char* value(const ::serial_mcu::robocupController_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x363960c0c6948d0cULL;
  static const uint64_t static_value2 = 0xf00f4ffede979e51ULL;
};

template<class ContainerAllocator>
struct DataType< ::serial_mcu::robocupController_<ContainerAllocator> >
{
  static const char* value()
  {
    return "serial_mcu/robocupController";
  }

  static const char* value(const ::serial_mcu::robocupController_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::serial_mcu::robocupController_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 firstHalf\n\
int64 kickoffTeam\n\
int64 state\n\
int64 penalty\n\
";
  }

  static const char* value(const ::serial_mcu::robocupController_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::serial_mcu::robocupController_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.firstHalf);
      stream.next(m.kickoffTeam);
      stream.next(m.state);
      stream.next(m.penalty);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct robocupController_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::serial_mcu::robocupController_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::serial_mcu::robocupController_<ContainerAllocator>& v)
  {
    s << indent << "firstHalf: ";
    Printer<int64_t>::stream(s, indent + "  ", v.firstHalf);
    s << indent << "kickoffTeam: ";
    Printer<int64_t>::stream(s, indent + "  ", v.kickoffTeam);
    s << indent << "state: ";
    Printer<int64_t>::stream(s, indent + "  ", v.state);
    s << indent << "penalty: ";
    Printer<int64_t>::stream(s, indent + "  ", v.penalty);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SERIAL_MCU_MESSAGE_ROBOCUPCONTROLLER_H
