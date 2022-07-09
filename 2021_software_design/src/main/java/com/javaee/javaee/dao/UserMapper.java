package com.javaee.javaee.dao;

import com.javaee.javaee.bean.User;
import org.apache.ibatis.annotations.*;
import org.springframework.data.repository.*;
import java.util.List;

@Mapper
public interface UserMapper {
    @Select("select * from user")
    List<User> findAll();

    @Insert("insert into user(userno, username, pwd, authority, receivetel, receivelo) values(#{userno}, #{username}, #{pwd}, #{authority}, #{receivetel}, #{receivelo})")
    public int add(User user);

    @Delete("delete from user where userno= #{userno}")
    public int delete(String userno);

    @Select("select * from user where userno= #{userno}")
    public User select(String userno);

    @Update("update user set username=#{username}, pwd=#{pwd}, receivetel=#{receivetel}, receivelo=#{receivelo} where userno=#{userno}")
    public int update(User user);
}
