package com.javaee.javaee.service;

import com.javaee.javaee.bean.Order;
import com.javaee.javaee.dao.OrderMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

@Service
public class OrderService{
    @Resource
    private OrderMapper orderMapper;

    public List<Order> findAll(){
        return orderMapper.findAll();
    }

    public int add(Order order){
        return orderMapper.add(order);
    }

    public int delete(String orderno){
        return orderMapper.delete(orderno);
    }

    public Order select(String orderno){
        return orderMapper.select(orderno);
    }

    public int update(Order order){
        return orderMapper.update(order);
    }
}
