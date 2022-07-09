package com.javaee.javaee.dao;

import com.javaee.javaee.bean.Order;
import org.apache.ibatis.annotations.*;
import org.springframework.data.repository.*;
import java.util.List;

@Mapper
public interface OrderMapper {
    @Select("select * from orders")
    List<Order> findAll();

    @Insert("insert into orders(orderno, userno, commodityno, quantity, location, tel) values(#{orderno}, #{userno}, #{commodityno}, #{quantity}, #{location}, #{tel})")
    public int add(Order order);

    @Delete("delete from orders where orderno= #{orderno}")
    public int delete(String orderno);

    @Select("select * from orders where orderno= #{orderno}")
    public Order select(String orderno);

    @Update("update orders set location=#{location}, tel=#{tel} where orderno=#{orderno}")
    public int update(Order order);
}
