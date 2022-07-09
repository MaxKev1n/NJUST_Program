package com.javaee.javaee.dao;

import com.javaee.javaee.bean.Commodity;
import org.apache.ibatis.annotations.*;
import org.springframework.data.repository.*;
import java.util.List;

@Mapper
public interface CommodityMapper {
    @Select("select * from commodity")
    List<Commodity> findAll();

    @Insert("insert into commodity(commodityno, commodityname, price, stock, details, pic, type) values(#{commodityno}, #{commodityname}, #{price}, #{stock}, #{details}, #{pic}, #{type})")
    public int add(Commodity commodity);

    @Delete("delete from commodity where commodityno= #{commodityno}")
    public int delete(String commodityno);

    @Select("select * from commodity where commodityno= #{commodityno}")
    public Commodity select(String commodityno);

    @Select("select * from commodity where type= #{type}")
    public List<Commodity> selectByType(int type);

    @Update("update commodity set price=#{price}, stock=#{stock}, details=#{details} where commodityno=#{commodityno}")
    public int update(Commodity commodity);
}
