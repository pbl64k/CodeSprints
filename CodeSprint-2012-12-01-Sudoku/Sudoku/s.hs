import Data.List
import Data.Array.Base
g=[1..9]
f=[1..3]
b=map
c=concat
e=zip g
o p=if null z then[p]else c$b o(b(\v->p//[(w,v)])(((g\\(b(\k->p!(k,j))g))\\(b(\k->p!(i,k))g))\\(b(p!)[(k+(i-1)`div`3*3,l+(j-1)`div`3*3)|k<-f,l<-f])))
 where
 z=[(i,j)|i<-g,j<-g,p!(i,j)<1]
 w@(i,j)=z!!0
u::[[Int]]->UArray(Int,Int)Int
u x=array((1,1),(9,9))(c$b(\(n,x)->b(\(m,y)->((m,n),y))(e x))(e x))
p[]=[]
p(' ':s)=p s
p s=let(c,r)=span(>' ')s in(read c):p r
main=(mapM(\x->getLine)g)>>=(\s->mapM(\y->(putStrLn.(intercalate" ").(b(\x->show(((head.o.u)(p`b`s))!(x,y)))))g)g)
