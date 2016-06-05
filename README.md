# LoveChat
提供完整消息分发方案。

1. 系统说明：
	1.1 gateserver说明（gs）
	1.2 chatserver说明(cs)
	1.3 loginserver说明(ls)
	1.4 dbserver说明(ds)
2. 模块关系图

	------------------------------------------------->
	@client				@cs

	...		@gs		...		@ds	
		
	@client				@cs

					@ls
	------------------------------------------------->
3. 模块设计
	3.1 gateserver设计
		接受客户端发送的消息，将登陆，注册，修改等的消息转发给ls模块。
		将ls返回信息发送给客户端，将服务器分配信息发送给客户端。
	3.2 chatserver设计
		聊天服务器，当玩家登陆成功，
	3.3 loginserver设计
	3.4 dbserver设计


