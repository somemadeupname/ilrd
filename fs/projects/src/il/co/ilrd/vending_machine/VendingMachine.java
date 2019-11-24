package il.co.ilrd.vending_machine;

import java.util.Collection;

public class VendingMachine {

    private State state;
    private int currBalance;
    private Product selectedProduct;
    private Collection<Product> items;
    private ViewModel view;

    public VendingMachine(Collection<Product> items, ViewModel view) {
    	this.items = items;
        this.view = view;
        state = State.begin;
    }

    /**
     * Initializes and invokes VendingMachine to begin state.
     */
    public void start() {
    	state.init(this);
    }

    /**
     * Insert money into machine.
     * @param money inserted for transaction.
     */
    public void pay(int money) {
    	
    	currBalance += money;
    	
    	if (currBalance >= selectedProduct.price) {
    		
    		state = State.waitForProduct;/* TODO should add more state? */
    	}

    }

    /**
     * Chooses product to buy.
     * @param chosen product.
     * invalid product will not have effect,
     * error message will be displayed in ViewModel.
     */
    public void chooseProduct(Product chosen) {
    }

    /**
     * cancels current transaction, and flushes change
     */
    public void cancel() {}

    private enum State {
        begin{
                @Override
                void init(VendingMachine vm) {
                	vm.state = waitForProduct;
                }
                @Override
                void cancel(VendingMachine vm){}
				@Override
				void timeout(VendingMachine vm) {
					// TODO Auto-generated method stub
				}
        },

        waitForMoney{
            @Override
            void pay(VendingMachine vm, int money){}
            @Override
            void cancel (VendingMachine vm){}
			@Override
			void timeout(VendingMachine vm) {
				// TODO Auto-generated method stub
				
			}
        },

        waitForProduct{
            @Override
            void chooseProduct(VendingMachine vm, Product product){}
            @Override
            void cancel (VendingMachine vm){}
			@Override
			void timeout(VendingMachine vm) {
				// TODO Auto-generated method stub
				
			}
        };

        /*
         *  Will initialize Vending machine, change to waitForProduct state
         * @param vm - current Vending Machine
         */
        void init(VendingMachine vm) {
        	vm.state = waitForProduct;
        }
       /*
        * Handles payment transaction, increases current balance,
        * changes state to chooseProduct if there is sufficient balance.
        */
        void pay(VendingMachine vm, int money) {
        	
        }

       /*
        * Changes selected product in vm, changes state to waitForMoney
        */
        void chooseProduct(VendingMachine vm, Product product) {
        	
        }

        /*
         * @param vm cancels current transaction,
         *  changes state to waitForProduct
         */
        void cancel(VendingMachine vm) {}
        
        abstract void timeout(VendingMachine vm);
       
        }
}

    class Product {
        public String name;
        public int price;

        Product(String name, int price) {
            this.price = price;
            this.name = name;
        }
        
        @Override
        public int hashCode() {
        	// TODO Auto-generated method stub
        	return super.hashCode();
        }
        
        @Override
        public boolean equals(Object obj) {
        	
        	
        	return super.equals(obj);
        }
        
        
    }

