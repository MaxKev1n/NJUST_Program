package com.javaee.javaee.service;

import com.javaee.javaee.bean.User;
import com.javaee.javaee.dao.UserMapper;
import com.javaee.javaee.service.UserService;
import org.springframework.stereotype.Service;
import javax.annotation.Resource;
import java.util.List;

@Service
public class UserService{
    @Resource
    private UserMapper userMapper;

    public List<User> findAll(){
        return userMapper.findAll();
    }

    public int add(User user){
        return userMapper.add(user);
    }

    public int delete(String userno){
        return userMapper.delete(userno);
    }

    public User select(String userno){
        return userMapper.select(userno);
    }

    public int update(User user){
        return userMapper.update(user);
    }

    public int login(User user){
        String userno = user.getUserno();
        String pwd = user.getPwd();
        int authority = user.getAuthority();
        User u = userMapper.select(userno);
        if(u == null){
            return 0;
        }else{
            if(u.getPwd().equals(pwd) && u.getAuthority() == authority){
                return 1;
            } else{
                return 2;
            }
        }
    }
}
