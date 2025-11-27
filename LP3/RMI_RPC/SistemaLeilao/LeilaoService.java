import java.rmi.Remote;
import java.rmi,RemoteException;
import java.util.list;

public interface LeilaoService extends Remote{
    void registrarCliente(ClienteCallback cliente) throws RemoteException;
}