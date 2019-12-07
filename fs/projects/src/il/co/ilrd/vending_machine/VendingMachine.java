package il.co.ilrd.vending_machine;

import java.security.Timestamp;
import java.util.Collection;
import java.util.Objects;

public class VendingMachine {

    private State state;
    private int currBalance;
    private Collection<Product> products;
    private ViewModule view;
    private Thread thread;
    private boolean active;
    private Timestamp startTime;

    public VendingMachine(Collection<Product> items, ViewModule view) {
        this.products = items;
        this.view = view;
        state = State.INIT;
        active = true;
        
        thread = new Thread ( () -> {

            while (active) {
                state.timeout(this);
                try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
            }
        });
    }

    /**
     * Initializes and invokes VendingMachine to begin state.
     */
    public void start() {
        state.init(this);
    }

    /**
     * Shutdown the VendingMachine.
     */
    public void shutDown() {
        state.shutDown(this);
    }

    /**
     * Insert money into machine.
     * @param coinValue inserted for transaction.
     */
    public void insertCoin(int coinValue) {
        state.insertCoin(this, coinValue);
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
    public void cancel() {
        state.cancel(this);
    }

    private enum State {
        INIT{
            @Override
            void init(VendingMachine vm) { /*FIXME init start time */
            }
            
            @Override
            void handleCurrentState (VendingMachine vm) {
            	
            }
            
        },

        IDLE {
        	@Override
        	void insertCoin(VendingMachine vm, int coinValue) {
        	}

        	@Override
        	void handleCurrentState (VendingMachine vm) {
        		
        	}
        	
        },

        COLLECTING_MONEY {
            
        	@Override
            void insertCoin(VendingMachine vm, int coinValue) {
            }

            @Override
            void chooseProduct(VendingMachine vm, Product product) {
            }

            void cancel (VendingMachine vm) {
            }

            @Override
            void timeout(VendingMachine vm) {
            }
            
            @Override
            void handleCurrentState (VendingMachine vm) {
            	
            }
            
        },

        TRANSACTION_COMPLETE {
            @Override
            void timeout(VendingMachine vm) {
            }
            
            @Override
            void handleCurrentState (VendingMachine vm) {
            	
            }
            
        };

        /*
         *  Will initialize Vending machine, change to waitForProduct state
         * @param vm - current Vending Machine
         */
        void init(VendingMachine vm) {

        }
        
        /*
         *  Will shut down Vending machine, change change active flag to false
         * @param vm - current Vending Machine
         */
        void shutDown(VendingMachine vm) {

        }
        /*
         * Handles payment transaction, increases current balance,
         * changes state to WAIT_FOR_PRODUCT if there is sufficient balance.
         */
        void insertCoin(VendingMachine vm, int money) {

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
        void cancel(VendingMachine vm){
        }

        /*
         * @param vm 
         *  handles timeout event 
         */
        void timeout (VendingMachine vm) {
        	
        }
        
        /*
         * @param vm 
         * sets start time to current time of state transition
         */
        abstract void handleCurrentState (VendingMachine vm);
    }

    public static class Product {
        private String name;
        private int price;

        Product(String name, int price) {
            this.price = price;
            this.name = name;
        }

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + ((name == null) ? 0 : name.hashCode());
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Product other = (Product) obj;
			if (name == null) {
				if (other.name != null)
					return false;
			} else if (!name.equals(other.name))
				return false;
			return true;
		}

    }

}