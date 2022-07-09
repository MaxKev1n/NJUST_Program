package com.javaee.javaee.service;

import com.javaee.javaee.bean.Commodity;
import com.javaee.javaee.dao.CommodityMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

@Service
public class CommodityService{
    @Resource
    private CommodityMapper commodityMapper;

    public List<Commodity> findAll(){
        return commodityMapper.findAll();
    }

    public int add(Commodity commodity){
        return commodityMapper.add(commodity);
    }

    public int delete(String commodityno){
        return commodityMapper.delete(commodityno);
    }

    public Commodity select(String commodityno){
        return commodityMapper.select(commodityno);
    }

    public int update(Commodity commodity){
        return commodityMapper.update(commodity);
    }

    public List<Commodity> selectByType(int type){
        return commodityMapper.selectByType(type);
    }
}

